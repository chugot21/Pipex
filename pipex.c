/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 15:09:57 by clara             #+#    #+#             */
/*   Updated: 2023/07/26 17:43:36 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    error_msg(char *msg)
{
    perror(msg);
    exit(1);
}

void    father(char **argv, int *pipefd, char **env)
{
    int outfilefd;

    outfilefd = open(argv[4], O_WRONLY, 0777);
    close(pipefd[1]);
    if (outfilefd == -1)
        error_msg("Error open\n");
    if ((dup2(pipefd[0], 0) == -1) || (dup2(outfilefd, 1) == -1))
        error_msg("Error dup2\n");
    if (execve(argv[4], argv + 1, env) == - 1)
        error_msg("error execve\n");
}

/*void    father(char **argv, int pipefd, char **env)
{
    char *buffer;
    int bytes;
    int outfd;
    int i;
    //int j; peut etre pour outfd, pour ne pas réécrire sur ce qui a deja ete ecrit.

    i = 0;
    //j = 0;
    //pipefd[1] = open("outfile.txt", O_WRONLY);
    if ((outfd = dup(pipefd[1])) == -1) //on utilise dup pour avoir acces au fd meme en fermant le pipe.
    {
        perror("error dup\n");
        exit (1);
    }
    close(pipefd[1]);
    while (bytes = read(pipefd[0], buffer, 42) > 0) //tant que read renvoie le nombre d'octets lus. 
    {
        while (i <= bytes)
        {
            write(outfd, &buffer[i], ft_strlen(buffer));
            i++;
        }
    }
    close(pipefd[0]);
}*/

void    son(char **argv, int *pipefd, char **env)
{
    int infilefd;
    int status;

    infilefd = open(argv[1], O_RDONLY, 0777);
    close(pipefd[0]); //on ne peut utiliser qu'une entree ou sortie du pipe en même temps.
    if (infilefd == -1)
        error_msg("Error open\n");
    if ((dup2(infilefd, 0) == -1) || (dup2(pipefd[1], 1) == -1))
        error_msg("Error dup2\n");
    if (execve(argv[2], argv + 1, env) == - 1)
        error_msg("error execve\n");
    wait(&status); //attendre la fin de l'execution du processus fils.
}

int main(int argc, char **argv, char **env)
{
    pid_t   pid; //retour de fork
    int pipefd[2];

    //pipefd = malloc(sizeof(int) * 2);
    if (argc != 5)
        error_msg("error argc\n");
    if (pipe(pipefd) == -1) //erreur pipe
        error_msg("error pipe\n");
    pid = fork();
    if (pid == -1) //erreur fork
        error_msg("error fork\n");
    else if (pid == 0) //processus fils - execution cmd1.
        son(argv, pipefd, env);
    father(argv, pipefd, env); //processus père - execution cmd2.
    return (0);
}
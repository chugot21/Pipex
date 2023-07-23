/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clara <clara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 15:09:57 by clara             #+#    #+#             */
/*   Updated: 2023/07/23 19:30:48 by clara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **env)
{
    pid_t   pid; //retour de fork
    int status;
    int pipefd[2];

    //pipefd = malloc(sizeof(int) * 2);
    if (argc < 4)
    {
        perror("error argc\n");
        exit (1);
    }
    pipefd[0] = open("infile.txt", O_RDONLY);
    pipefd[1] = open("outfile.txt", O_WRONLY);
    if (pipe(pipefd) == -1) //erreur pipe
    {
        perror("error pipe\n");
        exit (1);
    }
    if ((pid = fork()) == -1) //erreur fork
    {
        perror("error fork\n");
        exit (1);
    }
    else if (pid == 0) //processus fils
    {
        close(pipefd[0]); //on ne peut utiliser qu'une entree ou sortie du pipe en même temps, il faut donc en fermer tjs un cote.
        //if ((dup2(pipefd[1], 1)) == -1)
        //    perror("error dup2\n");
        if (execve(argv[2], argv + 1, env) == - 1)
        {
            perror("error execve\n");
            exit (1);
        }
        else //attendre la fin de l'execution du processus fils.
           wait(&status);
    }
    else //processus père
    {
        char *buffer;
        int bytes;
        int outfd;
        int i;
        //int j; peut etre pour outfd, pour ne pas réécrire sur ce qui a deja ete ecrit.

        i = 0;
        //j = 0;
        if ((outfd = dup(pipefd[1])) == -1) //on utilise dup pour avoir acces au fd meme en fermant le pipe.
        {
            perror("error dup\n");
            exit (1);
        }
        close(pipefd[1]);
        //manque execution de la deuxième cmd !!!
        //peut être utiliser GNL bonus pour ecrire dans outfd.
        while (bytes = read(pipefd[0], buffer, 42) > 0) //tant que read renvoie le nombre d'octets lus. 
        {
            while (i <= bytes)
            {
                write(outfd, &buffer[i], ft_strlen(buffer));
                i++;
            }
        }
        close(pipefd[0]);
    }
    return (0);
}
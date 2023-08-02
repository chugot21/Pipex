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

char	*check_path(char *cmd, char **env)
{
	char	**tabpath;
	char	*halfpath;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PATH=", 5) == NULL)
		i++;
	tabpath = ft_split(env[i] + 5, ':');
	i = 0;
	while (tabpath[i])
	{
		halfpath = ft_strjoin(tabpath[i], "/");
		path = ft_strjoin(halfpath, cmd);
		free(halfpath);
		if (access(path, F_OK) == 0)
		{
			free_tab(tabpath);
			return (path);
		}
		free(path);
		i++;
	}
	free_tab(tabpath);
	error_msg("error no path found\n");
}

void	path(char *argv, char **env)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = check_path(cmd[0], env);
	if (execve(path, cmd, env) == -1)
	{
		free_tab(cmd);
		free(path);
		error_msg("error execve\n");
	}
	free_tab(cmd);
	free(path);
}

void	father(char **argv, int *pipefd, char **env)
{
	int	outfilefd;

	outfilefd = open(argv[4], O_WRONLY, 0777);
	close(pipefd[1]);
	if (outfilefd == -1)
		error_msg("Error open\n");
	if ((dup2(pipefd[0], 0) == -1) || (dup2(outfilefd, 1) == -1))
		error_msg("Error dup2\n");
	path(argv[3], env);
}

void	son(char **argv, int *pipefd, char **env)
{
	int	infilefd;
	int	status;

	infilefd = open(argv[1], O_RDONLY, 0777);
	close(pipefd[0]);
	if (infilefd == -1)
		error_msg("Error open\n");
	if ((dup2(infilefd, 0) == -1) || (dup2(pipefd[1], 1) == -1))
		error_msg("Error dup2\n");
	path(argv[2], env);
	wait(&status);
}

int	main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		pipefd[2];

	if (argc != 5)
		error_msg("error argc\n");
	if (pipe(pipefd) == -1)
		error_msg("error pipe\n");
	pid = fork();
	if (pid == -1)
		error_msg("error fork\n");
	else if (pid == 0)
		son(argv, pipefd, env);
	father(argv, pipefd, env);
	return (0);
}

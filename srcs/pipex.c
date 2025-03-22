/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:40:35 by cmontaig          #+#    #+#             */
/*   Updated: 2025/03/22 13:35:10 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd(char *argv, char **env)
{
	t_pipex	pipex;
	char	**cmd;
	char	*path;

	if (!argv || !argv[0])
		exit(127);
	cmd = ft_split(argv, ' ');
	if (!cmd)
		exit (1);
	get_env_path(&pipex, env);
	path = find_command(pipex.path, cmd[0]);
	if (!path)
	{
		free_cmd(cmd);
		free_path(&pipex);
		exit(127);
	}
	execve(path, cmd, env);
	if (path != cmd[0])
		free(path);
	free_cmd(cmd);
	free_path(&pipex);
	exit_handler(errno);
}

void	parents(char **argv, char **env, int *fd)
{
	int	fd_out;

	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		exit(1);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd[0]);
	close(fd_out);
	execute_cmd(argv[3], env);
}

void	child(char **argv, char **env, int *fd)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY, 0777);
	if (fd_in == -1)
		exit(1);
	close(fd[0]);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd_in);
	close(fd[1]);
	execute_cmd(argv[2], env);
}

int	main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			exit (1);
		pid = fork();
		if (pid == -1)
			exit (1);
		if (pid)
		{
			waitpid(pid, &status, 0);
			parents(argv, env, fd);
		}
		else
			child(argv, env, fd);
	}
	else
	{
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
		exit (1);
	}
	return (0);
}

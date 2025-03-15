/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:40:35 by cmontaig          #+#    #+#             */
/*   Updated: 2025/03/15 15:16:11 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void execute_cmd(char *argv, char **env)
{
	t_pipex pipex;
	char	**cmd;
	int	 i;
	char	*path;
		
	i = -1;
	cmd = ft_split(argv, ' ');
	if (!cmd)
	{
		printf("error 11\n");
		exit (1);
	}
	get_env_path(&pipex, env);
	if (ft_strchr(cmd[0], '/') && access(cmd[0], X_OK) == 0)
		path = cmd[0];
	else
		path = find_command(pipex.path, cmd[0]);

	if (!path)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		if (pipex.path)
		{
			i = -1;
			while (pipex.path[++i])
				free(pipex.path[i]);
			free(pipex.path);
		}
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd("\n", 2);
		printf("error 12\n");
		exit(1);
	}

	if (execve(path, cmd, env) == -1)
	{
		if (path != cmd[0])
			free(path);
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		printf("error 13\n");
		exit (1);
	}
}

int main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		fd[2];
	(void)argc;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
		{
			printf("error 1\n");
			exit (1);
		}

		pid = fork();
		if (pid == -1)
		{
			printf("error 2\n");
			exit (1);
		}
			
		if (pid) // parents
		{
			int	fd_out;
			
			fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fd_out == -1)
				exit (1);
			dup2(fd[0], STDIN_FILENO);
			dup2(fd_out, STDOUT_FILENO);
			close(fd[1]);
			waitpid(pid, NULL, 0);
			execute_cmd(argv[3], env);
		}
		else //child 
		{
			int	fd_in;
			
			fd_in = open(argv[1], O_RDONLY, 0777);
			if (fd_in == -1)
				exit (1);
			dup2(fd[1], STDOUT_FILENO);
			dup2(fd_in, STDIN_FILENO);
			close(fd[0]);
			execute_cmd(argv[2], env);
		}
	}
	else
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	return (0);
}


// int	main(int ac, char **av)
// {
// 	__pid_t	pid = 0;
// 	int		exit_status;
// 	int		pipe_fd[2];

// 	pipe(pipe_fd);
// 	pid = fork();
// 	if (pid) // parents
// 	{
// 		int	fdstdint = dup(0);
// 		int	fdstdout = dup(1);
// 		int	fd_in = open("./InputFile", O_RDONLY);
		
// 		dup2(fd_in, 0);
// 		dup2(pipe_fd[1], 1);
// 		close(pipe_fd[0]);

// 		//cat

// 		close(0);
// 		close(1);
// 		dup2(fdstdint, 0);
// 		dup2(fdstdout, 1);
// 		close(fd_in); //
// 		close(pipe_fd[1]); //
// 		waitpid(pid, &exit_status, 0);
// 	}
// 	else // child
// 	{
// 		int	fdstdint = dup(0);
// 		int	fdstdout = dup(1);
// 		int	fd_out = open("./OutputFile", O_WRONLY | O_TRUNC);

// 		dup2(pipe_fd[0], 0);
// 		dup2(fd_out, 1);
// 		close(pipe_fd[1]);

// 		//grep
		
// 		close(0);
// 		close(1);
// 		dup2(fdstdint, 0);
// 		dup2(fdstdout, 1);
// 		close(fd_out);
// 		close(pipe_fd[0]);
// 		exit(42);
// 	}
// 	return (0);
// }

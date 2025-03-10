/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:40:35 by cmontaig          #+#    #+#             */
/*   Updated: 2025/03/10 13:57:48 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int	main(int ac, char **av)
// {
// 	__pid_t	pid = 0;
// 	int		exit_status;
// 	char	buffer[11];
// 	int		read_red;
// 	int		pipe_fd[2];

// 	pipe(pipe_fd);
// 	pid = fork();
// 	if (pid)
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
// 		waitpid(pid, &exit_status, 0);
// 	}
// 	else
// 	{
// 		int	fdstdint = dup(0);
// 		int	fdstdout = dup(1);
// 		int	fd_out = open("./OutputFile", O_WRONLY | O_TRUNC);

// 		dup2(fd_out, 0);
// 		dup2(pipe_fd[0], 0);
// 		close(pipe_fd[1]);

// 		//grep
		
// 		close(0);
// 		close(1);
// 		dup2(fdstdint, 0);
// 		dup2(fdstdout, 1);
// 		close(fd_out);
// 		exit(42);
// 	}
// }

int	main(int ac, char **av, char **env)
{
	t_list	pipex;
	__pid_t	pid = 0;
	int		exit_status;
	char	buffer[11];
	int		read_red;
	int		pipe_fd[2];

	get_env_path(&pipex, env); //

	pipe(pipe_fd);
	pid = fork();
	if (pid)
	{
		int	fdstdint = dup(0);
		int	fdstdout = dup(1);
		int	fd_in = open(av[1], O_RDONLY);
		
		dup2(fd_in, 0);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[0]);

		close(0);
		close(1);
		dup2(fdstdint, 0);
		dup2(fdstdout, 1);
		waitpid(pid, &exit_status, 0);
	}
	else
	{
		int	fdstdint = dup(0);
		int	fdstdout = dup(1);
		int	fd_out = open(av[4], O_WRONLY | O_TRUNC);

		dup2(fd_out, 0);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[1]);

		//grep
		
		close(0);
		close(1);
		dup2(fdstdint, 0);
		dup2(fdstdout, 1);
		close(fd_out);
		exit(42);
	}
}
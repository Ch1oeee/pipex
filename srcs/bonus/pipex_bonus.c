/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:15:25 by cmontaig          #+#    #+#             */
/*   Updated: 2025/04/03 17:31:39 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../../Libraries/libft/libft.h"
#include "../../Libraries/gnl/get_next_line.h"

void	wait_all(t_pipex *pipex)
{
	t_cmd	*temp;
	int		tmp;
	pid_t	pid_ret;

	temp = pipex->cmd;
	printf("Début de wait_all...\n");

	while (temp)
	{
		do {
			pid_ret = waitpid(temp->pid, &tmp, 0);
			if (pid_ret == -1)
			{
				perror("waitpid");
				break;
			}
		} while (pid_ret != temp->pid);

		printf("Processus %d terminé\n", temp->pid);
		temp = temp->next;
	}

	printf("Fin de wait_all...\n");

	if (WIFEXITED(tmp))
		if (WEXITSTATUS(tmp) > pipex->status)
			pipex->status = WEXITSTATUS(tmp);
}




// void	child_process(t_pipex *pipex, t_cmd *cmd, int *fd, char **env)
// {
// 	close(fd[0]);
// 	dup2(pipex->infile_fd, STDIN_FILENO);
// 	if (!cmd->next)
// 		dup2(pipex->outfile_fd, STDOUT_FILENO);
// 	else
// 		dup2(fd[1], STDOUT_FILENO);
// 	close(fd[1]);
// 	close(pipex->infile_fd);
// 	if (pipex->outfile_fd > 2)
// 		close(pipex->outfile_fd);
// 	if (execve(cmd->cmd_path, cmd->args, env) == -1)
// 	{
// 		perror(cmd->args[0]);
// 		exit(127);
// 	}
// }

void child_process(t_pipex *pipex, t_cmd *cmd, int *fd, char **env)
{
	close(fd[0]);
		
	if (pipex->infile_fd >= 0) 
	{
		dup2(pipex->infile_fd, STDIN_FILENO);
		close(pipex->infile_fd);
	}
	else
		close(STDIN_FILENO);
		
	if (!cmd->next)
		dup2(pipex->outfile_fd, STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);
		
	close(fd[1]);
	if (pipex->outfile_fd >= 0)
		close(pipex->outfile_fd);
		
	if (execve(cmd->cmd_path, cmd->args, env) == -1)
	{
		perror(cmd->args[0]);
		exit(127);
	}
}

void parent_process(t_pipex *pipex, int *fd)
{
	close(fd[1]); 
	if (pipex->infile_fd >= 0)
		close(pipex->infile_fd);
	pipex->infile_fd = dup(fd[0]); 
	close(fd[0]);
}


void	execute_cmd_b(t_pipex *pipex, char **env)
{
	int		fd[2];
	t_cmd	*temp;

	temp = pipex->cmd;
	while (temp)
	{
		if (!temp->args[0])
		{
			free_pipex(pipex);
			exit(127);
		}
		if (pipe(fd) < 0)
		{
			perror("pipe");
			free_pipex(pipex);
			exit(1);
		}
		temp->pid = fork();
		if (temp->pid == -1)
		{
			perror("fork");
			free_pipex(pipex);
			exit(1);
		}
		if (temp->pid == 0)
			child_process(pipex, temp, fd, env);
		else
			parent_process(pipex, fd);
		
		temp = temp->next;
	}
	wait_all(pipex);
}
int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	memset(&pipex, 0, sizeof(t_pipex));
	pipex.cmd = NULL;
	pipex.env = NULL;
	pipex.infile_fd = -1;
	pipex.outfile_fd = -1;
	pipex.status = 0;
	pipex.is_heredoc = 0;
	if (ac >= 5)
	{
		pipex.status = 0;
		pipex.infile_fd = -1;
		pipex.outfile_fd = -1;
		get_env_path(&pipex, env);
		create_list(&pipex, av, ac);
		execute_cmd_b(&pipex, env);
		printf("Les commandes ont été exécutées, sortie du programme...\n");

		if (pipex.status)
		{
			free_pipex(&pipex);
			exit(pipex.status);
		}
		free_pipex(&pipex);
	}
	else
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 ... cmd file2\n", 2);
	return (0);
}
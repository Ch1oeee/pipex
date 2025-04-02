/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:15:25 by cmontaig          #+#    #+#             */
/*   Updated: 2025/04/02 19:46:08 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../../Libraries/libft/libft.h"
#include "../../Libraries/gnl/get_next_line.h"

void	wait_all(t_pipex *pipex)
{
	t_cmd	*temp;
	int		status;

	temp = pipex->cmd;
	while (temp)
	{
		waitpid(temp->pid, &status, 0);
		if (WIFEXITED(status))
			pipex->status = WEXITSTATUS(status);
		temp = temp->next;
	}
}

void	child_process(t_pipex *pipex, t_cmd *cmd, int *fd, char **env)
{
	close(fd[0]);
	dup2(pipex->infile_fd, STDIN_FILENO);
	if (!cmd->next)
		dup2(pipex->outfile_fd, STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(pipex->infile_fd);
	if (pipex->outfile_fd > 2)
		close(pipex->outfile_fd);
	if (execve(cmd->cmd_path, cmd->args, env) == -1)
	{
		perror(cmd->args[0]);
		exit(127);
	}
}

void	parent_process(t_pipex *pipex, int *fd)
{
	close(fd[1]);
	close(pipex->infile_fd);
	pipex->infile_fd = dup(fd[0]);
	close(fd[0]);
}

void	handle_heredoc(t_pipex *pipex, char *limiter)
{
	char	*line;
	char	*prompt;

	prompt = "> ";
	pipex->infile_fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->infile_fd < 0)
	{
		perror(".heredoc_tmp");
		exit(1);
	}
	while (1)
	{
		write(STDOUT_FILENO, prompt, ft_strlen(prompt));
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && 
			line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break;
		}
		write(pipex->infile_fd, line, ft_strlen(line));
		free(line);
	}
	close(pipex->infile_fd);
	pipex->infile_fd = open(".heredoc_tmp", O_RDONLY);
	if (pipex->infile_fd < 0)
	{
		perror(".heredoc_tmp");
		exit(1);
	}
}

void	open_files(t_pipex *pipex, char **av, int ac)
{
	if (pipex->is_heredoc)
	{
		handle_heredoc(pipex, av[2]);
		pipex->outfile_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		pipex->infile_fd = open(av[1], O_RDONLY);
		if (pipex->infile_fd < 0)
		{
			perror(av[1]);
			pipex->status = 1;
		}
		pipex->outfile_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
		
	if (pipex->outfile_fd < 0)
	{
		perror(av[ac - 1]);
		if (pipex->infile_fd > 2)
			close(pipex->infile_fd);
		exit(1);
	}
}

void	execute_cmd_b(t_pipex *pipex, char **env)
{
	int		fd[2];
	t_cmd	*temp;

	temp = pipex->cmd;
	while (temp)
	{
		if (!temp->args[0])
			exit(127);
		
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

	if (ac < 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2\n", 2);
		return (1);
	}
	ft_memset(&pipex, 0, sizeof(t_pipex));
	pipex.infile_fd = -1;
	pipex.outfile_fd = -1;
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (ac < 6)
		{
			ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd1 cmd2 file\n", 2);
			return (1);
		}
		pipex.is_heredoc = true;
	}
	get_env_path(&pipex, env);
	open_files(&pipex, av, ac);
	create_list(&pipex, av, ac);
	execute_cmd_b(&pipex, env);
	free_pipex(&pipex);
	return (pipex.status);
}
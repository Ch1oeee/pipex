/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:15:49 by cmontaig          #+#    #+#             */
/*   Updated: 2025/04/02 19:26:25 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	exit_handler(int error_code)
{
	if (error_code == EACCES)
		exit(126);
	else
		exit(127);
}

void	free_path(t_pipex *pipex)
{
	int	i;

	if (pipex->path)
	{
		i = -1;
		while (pipex->path[++i])
			free(pipex->path[i]);
		free(pipex->path);
	}
}

void	free_cmd(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		free(cmd[i]);
	free(cmd);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*temp;
	int		i;
	while (cmd)
	{
		temp = cmd;
		cmd = cmd->next;
		i = 0;
		while (temp->args && temp->args[i])
			free(temp->args[i++]);
		if (temp->args)
			free(temp->args);
		if (temp->cmd_path && temp->cmd_path != temp->args[0])
			free(temp->cmd_path);
		free(temp);
	}
}

void	free_pipex(t_pipex *pipex)
{
	int	i;

	if (pipex->env)
	{
		i = 0;
		while (pipex->env[i])
			free(pipex->env[i++]);
		free(pipex->env);
	}
	if (pipex->path)
	{
		i = 0;
		while (pipex->path[i])
			free(pipex->path[i++]);
		free(pipex->path);
	}
	if (pipex->infile_fd > 2)
		close(pipex->infile_fd);
	if (pipex->outfile_fd > 2)
		close(pipex->outfile_fd);
}
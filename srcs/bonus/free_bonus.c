/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:15:49 by cmontaig          #+#    #+#             */
/*   Updated: 2025/04/03 16:43:44 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
void	free_pipex(t_pipex *pipex)
{
	int		i;
	t_cmd	*tmp;
	t_cmd	*next;

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
	tmp = pipex->cmd;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->args)
		{
			i = 0;
			while (tmp->args[i])
				free(tmp->args[i++]);
			free(tmp->args);
		}
		if (tmp->cmd_path)
			free(tmp->cmd_path);
		free(tmp);
		tmp = next;
	}
	pipex->cmd = NULL;
	if (pipex->infile_fd > 2)
		close(pipex->infile_fd);
	if (pipex->outfile_fd > 2)
		close(pipex->outfile_fd);
}

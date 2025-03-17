/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:40:15 by cmontaig          #+#    #+#             */
/*   Updated: 2025/03/17 17:47:42 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:36:38 by cmontaig          #+#    #+#             */
/*   Updated: 2025/04/02 18:48:33 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../../Libraries/libft/libft.h"

void	get_env_path(t_pipex *pipex, char **env)
{
	int		i;
	int		j;
	char	**path;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (strncmp("PATH=", env[i], 5) == 0)
		{
			path = ft_split(env[i] + 5, ':');
			j = 0;
			while (path[j])
			{
				pipex->env[j] = ft_strjoin(path[j], "/");
				free(path[j]);
				j++;
			}
			pipex->env[j] = NULL;
			return ;
		}
		i++;
	}
	free(path);
}

char	*find_command_b(t_pipex *pipex, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	full_path = NULL;
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	while (pipex->env[i++])
	{
		full_path = ft_strjoin(pipex->env[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (ft_strdup(cmd));
}
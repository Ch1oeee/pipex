/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:54:41 by cmontaig          #+#    #+#             */
/*   Updated: 2025/03/15 16:23:25 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../Libraries/libft/libft.h"

void	get_env_path(t_pipex *pipex, char **env)
{
	int	i;
	
	i = 0;
	while(env[i])
	{
		if (strncmp("PATH=", env[i], 5) == 0)
		{
			pipex->path = ft_split(env[i] + 5, ':');
			return ;
		}
		i++;
	}
	pipex->path = NULL;
}

char *find_command(char **path_dirs, char *cmd)
{
	int		i;
	char	*full_path;
	char	*slash_path;
	
	i = 0;
	full_path = NULL;

	//verif chemin absolu maybeeee
	
	while (path_dirs[i])
	{
		slash_path = ft_strjoin(path_dirs[i], "/");
		full_path = ft_strjoin(slash_path, cmd);
		free(slash_path);
		if (access(full_path, X_OK) == 0)
			return full_path;
		free(full_path);
		i++;
	}
	return NULL;
}




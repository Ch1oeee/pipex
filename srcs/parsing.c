/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:54:41 by cmontaig          #+#    #+#             */
/*   Updated: 2025/03/10 15:50:43 by cmontaig         ###   ########.fr       */
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
	while (path_dirs[i])
	{
		slash_path = ft_strjoin(full_path[i], "/");
		full_path = ft_strjoin(full_path[i], cmd);
		if (access(full_path, X_OK) == 0)
			return full_path;
		free(full_path);
		i++;
	}
	return NULL;
}

void print_paths(char **paths)
{
	int	i;

	if (!paths)
	{
		printf("Aucun chemin trouvé\n");
		return;
	}
	i = 0;
	while (paths[i])
	{
		printf("Chemin %d: %s\n", i, paths[i]);
		i++;
	}
}

int main(int argc, char **argv, char **env)
{
	t_pipex pipex;
	(void)argv;
	(void)argc;

	get_env_path(&pipex, env);
	printf("== Chemins trouvés ==\n");
	print_paths(pipex.path);
	
	return 0;
}

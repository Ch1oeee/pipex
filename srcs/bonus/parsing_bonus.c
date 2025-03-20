/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:36:38 by cmontaig          #+#    #+#             */
/*   Updated: 2025/03/20 16:37:03 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../../Libraries/libft/libft.h"

void	get_env_path(t_pipex *pipex, char **env)
{
	int	i;

	i = 0;
	while (env[i])
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
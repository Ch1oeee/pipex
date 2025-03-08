/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:54:41 by cmontaig          #+#    #+#             */
/*   Updated: 2025/03/07 16:21:37 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_env_path(t_pipex *pipex, char **env)
{
	int	i;
	
	i = 0;
	while(env[i])
	{
		if(ft_strstr(env[i], "PATH="))
		{
			pipex->path = ft_split(env[i] + 5, ":");
			return ;
		}
		i++;
	}
	pipex->path = NULL;
}
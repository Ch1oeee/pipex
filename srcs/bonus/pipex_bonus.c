/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:15:25 by cmontaig          #+#    #+#             */
/*   Updated: 2025/03/22 17:19:42 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../../Libraries/libft/libft.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int	fd[2];
	int status;
	
	if (argc >= 5)
	{
		
	}
	else
	{
		ft_putstr_fd("Missing arguments\n", 1);
		exit (1);
	}
	return (0);
}

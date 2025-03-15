/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:03:20 by cmontaig          #+#    #+#             */
/*   Updated: 2025/03/12 13:57:46 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../Libraries/libft/libft.h"
# include "../Libraries/ft_printf/ft_printf.h"

typedef struct pipex
{
	char	**env;
	char	**path;
}			t_pipex;

char	*find_command(char **path_dirs, char *cmd);
void	get_env_path(t_pipex *pipex, char **env);

#endif
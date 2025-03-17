/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:03:20 by cmontaig          #+#    #+#             */
/*   Updated: 2025/03/17 17:44:46 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
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
void	free_path(t_pipex *pipex);
void	free_cmd(char **cmd);
void	exit_handler(int error_code);
void	execute_cmd(char *argv, char **env);
void	parents(char **argv, char **env, int *fd);
void	child(char **argv, char **env, int *fd);

#endif
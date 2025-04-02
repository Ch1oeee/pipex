/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:03:20 by cmontaig          #+#    #+#             */
/*   Updated: 2025/04/02 19:48:27 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "../Libraries/libft/libft.h"
# include "../Libraries/ft_printf/ft_printf.h"

typedef struct cmd
{
	pid_t		pid;
	char		**args;
	char		*cmd_path;
	struct cmd	*next;
}			t_cmd;

typedef struct pipex
{
	char	**env;
	char	**path;
	bool	is_heredoc;
	int		infile_fd;
	int		outfile_fd;
	int		status;
	t_cmd	*cmd;
}			t_pipex;

char	*find_command(char **path_dirs, char *cmd);
void	get_env_path(t_pipex *pipex, char **env);
void	free_path(t_pipex *pipex);
void	free_cmd(char **cmd);
void	exit_handler(int error_code);
void	execute_cmd(char *argv, char **env);
void	parents(char **argv, char **env, int *fd);
void	child(char **argv, char **env, int *fd);

//BONUS
void	cmd_add_back(t_cmd **cmd, t_cmd *new);
t_cmd	*cmd_last(t_cmd *cmd);
t_cmd	*cmd_new(char *argv, t_pipex pipex);
void	create_list(t_pipex *pipex, char **argv, int ac);
void	free_pipex(t_pipex *pipex);
char	*find_command_b(t_pipex *pipex, char *cmd);
void	execute_cmd_b(t_pipex *pipex, char **env);
void	free_cmd_list(t_cmd *cmd);
void	free_pipex(t_pipex *pipex);


#endif
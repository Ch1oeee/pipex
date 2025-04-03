/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:53:07 by cmontaig          #+#    #+#             */
/*   Updated: 2025/04/03 14:58:23 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "../../Libraries/libft/libft.h"
# include "../../Libraries/ft_printf/ft_printf.h"

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

// BONUS
void	cmd_add_back(t_cmd **cmd, t_cmd *new);
t_cmd	*cmd_last(t_cmd *cmd);
t_cmd	*cmd_new(char *argv, t_pipex pipex);
void	create_list(t_pipex *pipex, char **argv, int ac);
void	free_pipex(t_pipex *pipex);
char	*find_command_b(t_pipex *pipex, char *cmd);
void	execute_cmd_b(t_pipex *pipex, char **env);
void	free_cmd_list(t_cmd *cmd);
void	free_pipex(t_pipex *pipex);
void	get_env_path(t_pipex *pipex, char **env);



#endif
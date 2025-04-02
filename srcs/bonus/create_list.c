/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmontaig <cmontaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:35:58 by cmontaig          #+#    #+#             */
/*   Updated: 2025/04/02 18:49:30 by cmontaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "../../Libraries/libft/libft.h"

void	cmd_add_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*cmd_2;

	if (cmd == NULL)
		return ;
	if (*cmd == NULL)
	{
		*cmd = new;
		return ;
	}
	cmd_2 = cmd_last(*cmd);
	cmd_2->next = new;
}

t_cmd	*cmd_last(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

t_cmd	*cmd_new(char *argv, t_pipex pipex)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->args = ft_split(argv, ' ');
	if (!new->args || !new->args[0])
	{
		free(new);
		return (NULL);
	}
	new->cmd_path = find_command_b(&pipex, new->args[0]);
	new->pid = 0;
	new->next = NULL;
	return (new);
}

void	create_list(t_pipex *pipex, char **argv, int ac)
{
	int	i;
	t_cmd *new_cmd;

	i = 2 + pipex->is_heredoc;
	while (i < ac - 1)
	{
		new_cmd = cmd_new(argv[i], *pipex);
		if (!new_cmd)
		{
			printf("error while trying to fill cmd list");
			return ;
		}
		cmd_add_back(&pipex->cmd, new_cmd);
		i++;
	}
}

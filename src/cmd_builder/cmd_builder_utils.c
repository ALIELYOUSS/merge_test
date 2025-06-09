/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:45:09 by yael-maa          #+#    #+#             */
/*   Updated: 2025/06/08 18:44:31 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    clear_directions(t_redir *redir)
{
	t_redir *tmp;

	while (tmp)
	{
		tmp = redir;
		redir = redir->next;
		if (tmp->file)
		{
			free(tmp->file);
			tmp->file = NULL;
		}
		free(tmp);
	}
}

void    clear_cmd(t_cmd *cmd)
{
    t_cmd   *tmp;

    while (cmd)
    {
        tmp = cmd;
        cmd = cmd->next;
        if (tmp->cmd)
        {
            free(tmp->cmd);
            tmp->cmd = NULL;
        }
		if (tmp->redir)
			clear_directions(tmp->redir);
        if (tmp)
        {
            free(tmp);
            tmp = NULL;
            cmd = NULL;
        }
    }
}


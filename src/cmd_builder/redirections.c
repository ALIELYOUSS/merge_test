/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 03:14:28 by yael-maa          #+#    #+#             */
/*   Updated: 2025/05/24 15:11:46 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_redir	*last_redir(t_redir *redir)
{
	t_redir	*tmp;
	
	tmp = redir;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_redir	*new_redir(char *content, t_type type)
{
    t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (write(2, "Memory Error\n", 13), NULL);
	new->file = content;
	new->type = type;
	new->next = NULL;
	return (new);
}

// void	add_redir(t_cmd **cmd, t_redir *new)
// {
// 	t_cmd	*tmp_c;
// 	t_redir	*tmp_r;
// 	t_redir	*tmp;

// 	if (!cmd || !(*cmd) || new)
// 		return ;
// 	if (!last_cmd(cmd)->redir)
// 		last_cmd(cmd)->redir = new;
// 	else
// 	{
// 		tmp_c = last_cmd(cmd);
// 		tmp_r = tmp_c->redir;
// 		tmp = last_redir(tmp_r);
// 		tmp->next = new;
// 	}
// }

void	add_redir(t_cmd **cmd, t_redir *new)
{
	t_cmd	*tmp_c;
	t_redir	*tmp_r;
	t_redir	*tmp;

	if (!cmd || !(*cmd) || !new)
		return ;
	tmp_c = last_cmd(cmd);
	if (!tmp_c->redir)
		tmp_c->redir = new;
	else
	{
		tmp_r = tmp_c->redir;
		tmp = last_redir(tmp_r);
		tmp->next = new;
	}
}
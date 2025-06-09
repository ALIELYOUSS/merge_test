/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:43:02 by yael-maa          #+#    #+#             */
/*   Updated: 2025/06/02 17:19:07 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*last_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	if (!cmd || !*cmd)
		return (NULL);
	tmp = *cmd;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_cmd	*new_cmd(char *content, t_redir *redir, t_type type)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (write(2, "Memory Error\n", 13), NULL);
	new->cmd = content;
	new->redir = redir;
	new->type = type;
	new->next = NULL;
	return (new);
}

char	*join_it(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	if (!s1 && !s2)
		return (NULL);
	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!s3)
		return (write(2, "Memory Error\n", 13), free(s1), s1 = NULL, free(s2), s2 = NULL, NULL);
	i = -1;
	while (s1[++i])
		s3[i] = s1[i];
	s3[i++] = ' ';
	j = -1;
	while (s2[++j])
		s3[i + j] = s2[j];
		// free(s2);
	s3[i + j] = '\0';
	// free (s1);
	return (s3);
}

void	add_cmd(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*tmp;
	
	if (!cmd || !new)
		return ;
	if (!(*cmd))
		*cmd = new;
	else
	{
		tmp = last_cmd(cmd);
		tmp->next = new;
	}
}

t_cmd	*build_cmd(t_list *tokens)
{
	t_tokens	*token;
	t_cmd		*cmd;
	int		f;

	cmd = NULL;
	if (!tokens || !tokens->head)
		return (NULL);
	// cmd = malloc(sizeof(t_cmd));
	// if (!cmd)
	// 	return (write(2, "Memory Error\n", 13), NULL);
	f = 0;
	token = tokens->head;
	// if (is_redir(token))
	// {
	// 	cmd = new_cmd(NULL, new_redir(token->next->content, token->type), token->type);
	// 	if (!cmd)
	// 		return (NULL);
	// 	token = token->next->next;
	// 	f = IN;
	// }
	while (token)
	{
		if (!operator(token))
		{
			if (!is_redir(token))
			{
				if (f == 0)
				{
					add_cmd(&cmd, new_cmd(token->content, NULL, CMD));
					token = token->next;
					f = 1;
				}
				else
				{
					while (token && !operator(token) && !is_redir(token))
					{
						t_cmd *last = last_cmd(&cmd);
						if (last)
							last->cmd = join_it(last->cmd, token->content);
						
						token = token->next;
					}
					// f = 1;
				}
				if (!token)
					break ;
			}
			if (is_redir(token))
			{
				add_redir(&cmd, new_redir(token->next->content, token->type));
				token = token->next;
				token = token->next;
				f = 1;
			}
		}
		if (operator(token))
		{
			// printf("1\n");
			add_cmd(&cmd, new_cmd(NULL, NULL, token->type));
			token = token->next;
			f = 0;
		}
		if (!token)
			break ;
	}
	return (cmd);
}
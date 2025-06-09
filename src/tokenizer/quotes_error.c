/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:48:14 by yael-maa          #+#    #+#             */
/*   Updated: 2025/05/20 23:53:00 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	quotes_syntax_error(void)
{
	write(2, "Syntax Error 2\n", 15);
	return ;
}

int	quotes_closed(char *content, int *index, char c)
{
	int	i;

	i = *index;
	while (content[++i])
	{
		if (content[i] == c)
			return (1);
	}
	return (0);
}

int	found_quotes_helper(char *content, int *i, int *tmp, char c)
{
	if (quotes_closed(content, tmp, c))
	{
		while (content[++(*i)] && content[*i] != c)
			;
	}
	else
	{
		quotes_syntax_error();
		return (0);
	}
	return (1);
}

void	found_quotes(char *content, int *i)
{
	int	tmp;

	tmp = *i;
	if ((content[tmp] == '"' || content[tmp] == '\''))
	{
		if (content[tmp] == '"')
		{
			if (!found_quotes_helper(content, i, &tmp, '"'))
				return ;
		}
		else if (content[tmp] == '\'')
		{
			if (!found_quotes_helper(content, i, &tmp, '\''))
				return ;
		}
	}
}

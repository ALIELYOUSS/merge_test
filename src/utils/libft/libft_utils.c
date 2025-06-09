/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:38:25 by yael-maa          #+#    #+#             */
/*   Updated: 2025/06/09 15:49:34 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp( char *s1,  char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

t_tokens	*create_token(void *content, int t)
{
	t_tokens	*new;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	new->next = NULL;
	new->type = t;
	return (new);
}

void	add_node(t_list *tokens, t_tokens *token)
{
	if (!tokens || !token)
		return ;
	if (tokens->size == 0)
	{
		tokens->head = token;
		tokens->tail = token;
		tokens->size++;
		return ;
	}
	tokens->tail->next = token;
	tokens->tail = token;
	tokens->size++;
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*c;
	size_t			i;

	c = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		c[i] = 0;
		i++;
	}
}

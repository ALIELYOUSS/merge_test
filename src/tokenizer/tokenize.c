/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:24:00 by yael-maa          #+#    #+#             */
/*   Updated: 2025/05/25 09:43:32 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	word_tokenizer(t_list *tokens, char *content, int *i)
{
	char		*word;
	t_tokens	*token;

	word = get_word(content, i);
	if (!word)
	{
		if (tokens)
			clear_list(tokens);
		write(2, "Memory Error\n", 13);
		exit(0);
	}
	token = create_token(word, WORD);
	free(word);
	if (!token)
	{
		if (tokens->size)
			clear_list(tokens);
		write(2, "memory Error\n", 13);
		exit(0);
	}
	add_node(tokens, token);
}

void	redir_and_hrdc(t_list *tokens, char *content, int *i)
{
	if (content[*i] == '<' && content[*i + 1] != '<')
		add_node(tokens, create_token("<", IN));
	else if (content[*i] == '>' && content[*i + 1] != '>')
		add_node(tokens, create_token(">", OUT));
	else if (content[*i] == '>' && content[*i + 1] == '>')
	{
		add_node(tokens, create_token(">>", APP));
		(*i)++;
	}
	else if (content[*i] == '<' && content[*i + 1] == '<')
	{
		add_node(tokens, create_token("<<", HRDOC));
		(*i)++;
	}
}

void	pipe_and_or(t_list *tokens, char *content, int *i)
{
	if (content[*i + 1] == '|')
	{
		add_node(tokens, create_token("||", OR));
		(*i)++;
	}
	else
		add_node(tokens, create_token("|", PIPE));
}

void	tokenizer_helper(t_list *tokens, char *content, int *i)
{
	if (content[*i] == '<' || content[*i] == '>')
		redir_and_hrdc(tokens, content, i);
	else if (content[*i] == '|')
		pipe_and_or(tokens, content, i);
	else if (content[*i] == '&' && content[*i + 1] == '&')
	{
		add_node(tokens, create_token("&&", AND));
		(*i)++;
	}
	else if (content[*i] == '(' || content[*i] == ')')
	{
		if (content[*i] == '(')
			add_node(tokens, create_token("(", LP));
		else
			add_node(tokens, create_token(")", RP));
	}
}

void	tokenizer(t_list *tokens, char *content, int *i)
{
	while (content[*i] && *i < ft_strlen(content))
	{
		while (content[*i] && ft_isspace(content[*i]))
			(*i)++;
		if (content[*i] && for_word(content[*i]) && !ft_isspace(content[*i]))
			word_tokenizer(tokens, content, i);
		else if (content[*i] && !for_word(content[*i])
			&& !ft_isspace(content[*i]))
		{
			tokenizer_helper(tokens, content, i);
			(*i)++;
		}
		if (content[*i] == '\0' || *i >= ft_strlen(content))
			break ;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 00:06:06 by yael-maa          #+#    #+#             */
/*   Updated: 2025/06/22 20:00:26 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	clear_list(t_list *tokens)
{
	t_tokens	*tmp;
	while (tokens->head)
	{
		tmp = tokens->head;
		tokens->head = tokens->head->next;
		if (tmp->content)
		{
			free(tmp->content);
			tmp->content = NULL;
		}
		if (tmp)
			free(tmp);
		tokens->size--;
		tmp = NULL;
	}
	tokens = NULL;
}

int	delimiter(char *str, char *c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) || !for_word(str[i]) || str[i] == '"' || str[i] == '\'')
		{
			*c = str[i];
			return (0);
		}
		i++;
	}
	if (str[i] == '\0')
	{
		*c = '\0';
		return (0);
	}
	return (1);
}

void	print_list(t_list *tokens)
{
	t_tokens	*tmp;

	tmp = tokens->head;
	while (tmp != tokens->tail)
	{
		printf("---------------content------------- :%s\n", tmp->content);
		printf("---------------type------------- :%d\n", tmp->type);
		tmp = tmp->next;
	}
	printf("-------------content------------ :%s\n", tmp->content);
	printf("---------------type------------- :%d\n", tmp->type);
}

// void	reset_param(t_list *tokens, char *content)
// {
// 	tokens = NULL;
// 	content = NULL;
// }

void	print_cmd(t_cmd *cmd)
{
	t_cmd *tmp;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->cmd)
			printf("%s\n", tmp->cmd);
		else 
			printf("%d\n", tmp->type);
		tmp = tmp->next;
	}
}

void	print_cmd_list(t_cmd *cmd)
{
	t_cmd *tmp = cmd;
	while (tmp)
	{
		if (tmp->cmd)
			printf("cmd: %s\n", tmp->cmd);
		printf("type: %d\n", tmp->type);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **env)
{
	char			*prompt;
	static char		*content;
	t_list			tokens;
	t_cmd			*cmd;
	t_env			*env_list;
	int				i;
	// t_redir			*redir;

	(void)ac;
	(void)av;
	tokens.size = 0;
	ft_bzero(&tokens, sizeof(t_list));
	env_list = fill_env_list(env);
	if (!env_list)
		return (-1);
	while (1)
	{
		// reset_param(&tokens, content);
		prompt = readline("~/minishell$ ✗ ");
		if (!finish_prompt(prompt))
			break ;
		if (!prompt)
			break ;
		add_history(prompt);
		content = str_trim(prompt);
		free(prompt);
		if (!content || !*content)
		{
			free(content);
			continue ;
		}
		i = 0;
		tokenizer(&tokens, content, &i);
		free(content);
		syntax_errors(&tokens);
 		cmd = build_cmd(&tokens);
		if (!cmd)
			break ;
		else if (is_heredoc(cmd))
			handle_heredoc(cmd, env_list, env);
		execution(cmd, env);
		if (tokens.size)
			clear_list(&tokens);
	}
	if (tokens.size)
		clear_list(&tokens);
	return (0);
}

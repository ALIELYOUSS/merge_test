#include "inc/minishell.h"

int	its_token(t_tokens *tokens, t_type type)
{
	if (tokens->type == type)
		return (1);
	return (0);
}

int	find_token(t_tokens *tokens, t_type type)
{
	t_tokens	*tmp;
	
	tmp = tokens;
	while (tmp)
	{
		if (its_token(tmp, type))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	main(int ac, char **av)
{
	char			*prompt;
	static char		*content;
	t_list			tokens;
    t_garbage       *garbage;
	int				i;

	(void)ac;
	(void)av;
	ft_bzero(&tokens, sizeof(t_list));
	tokens.size = 0;
	while (1)
	{
		prompt = readline("~/minishell$ ✗ ");
		if (!finish_prompt(prompt))
			break ;
		if (!prompt)
			break ;
		content = str_trim(prompt);
		free(prompt);
		if (!content || !*content)
		{
            write(2, "Memory Error\n", 13);
            if (tokens.size)
                clear_list(&tokens);
            exit(0);
        }
        garbage_collector(&garbage, add_garbage(content, NULL));
		i = 0;
		tokenizer(&tokens, content, &i);
        garbage_collector(&garbage, add_garbage(NULL, &tokens));
	}
	return (0);
}

// int	to_alloc(t_tokens *token)
// {
// 	t_tokens	*tmp;
// 	int			i;
// 	int			c;

// 	tmp = token;
// 	while (tmp && !operator(tmp))
// 	{
// 		i = 0;
// 		while (tmp->content[i++])
// 			c++;
// 		c++;
// 		tmp = tmp->next;
// 	}
// 	return (c);
// }

// char	*cmd(t_tokens *token)
// {
// 	char	*cmd_l;
// 	int		i;
// 	int		j;

// 	cmd_l = malloc(to_alloc(token));
// 	if (!cmd_l)
// 		return (NULL);
// 	j = 0;
// 	while (token && !operator(token))
// 	{
// 		i = 0;
// 		while (token->content[i])
// 			cmd_l[j++] = token->content[i++];
// 		cmd_l[j] = ' ';
// 		token = token->next;
// 	}
// 	cmd_l[j] = '\0';
// 	return (cmd_l);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_rem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:10:25 by yael-maa          #+#    #+#             */
/*   Updated: 2025/06/16 11:53:19 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	quotes_ps(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
			return (1);
	}
	return (0);
}

void	flag_quotes(char *cmd, int *flag)
{
	int	i;

	i = 0;
	while(cmd[i] && i < ft_strlen(cmd))
	{
		if (cmd[i] && cmd[i] == '"' && (i == 0 || cmd[i - 1] != '\\'))
		{
			cmd[i] = -1;
			i++;
			while (cmd[i] && cmd[i] != '"')
			{
				if (cmd[i] == '\\')
					i++;
				if (cmd[i])
					i++;
			}
			cmd[i] = -1;
			(*flag) += 2;
			i++;
		}
		if (cmd[i] && cmd[i] == '\'' && (i == 0 || cmd[i - 1] != '\\'))
		{
			cmd[i] = -1;
			i++;
			while (cmd[i] && cmd[i] != '\'')
			{
				if (cmd[i] == '\\')
					i++;
				if (cmd[i])
					i++;
			}
			cmd[i] = -1;
			(*flag) += 2;
			i++;
		}
		if (cmd[i] && cmd[i] != '"' && cmd[i] != '\'')
			i++;
		// if (cmd[i] && cmd[i] == '"')
		// {
		// 	(*flag)++;
		// 	while(cmd[i])
		// 	{
		// 		cmd[i] = -1;
		// 		i++;
		// 		if (cmd[i] && cmd[i] == '"')
		// 		{
		// 			(*flag)++;
		// 			cmd[i] = -1;
		// 			i++;
		// 			break ;
		// 		}
		// 		i++;
		// 	}
		// }
		// else if (cmd[i] && cmd[i] == '\'')
		// {
		// 	(*flag)++;
		// 	while(cmd[i])
		// 	{
		// 		cmd[i] = -1;
		// 		i++;
		// 		if (cmd[i] && cmd[i] == '\'')
		// 		{
		// 			(*flag)++;
		// 			cmd[i] = -1;
		// 			i++;
		// 			break ;
		// 		}
		// 		i++;
		// 	}
		// }
		// if (i < ft_strlen(cmd))
		// 	i++;
	}
}

char	*replace_quotes(char *cmd)
{
	int		f;
	char	*final_cmd;
	int		i;
	int		j;

	f = 0;
	flag_quotes(cmd, &f);
	final_cmd = malloc(ft_strlen(cmd) - f + 1);
	if (!final_cmd)
		return (write(2, "Memory Error\n", 13), NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(cmd))
	{
		if (cmd[i] == -1)
			i++;
		if (cmd[i] && cmd[i] != -1)
		{
			printf("HERE\n");
			final_cmd[j] = cmd[i];
			j++;
			i++;
		}
	}
	final_cmd[j] = '\0';
	return (final_cmd);
}

void	remove_quotes(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == CMD && quotes_ps(tmp->cmd))
			tmp->cmd = replace_quotes(tmp->cmd);
		tmp = tmp->next;
	}
}
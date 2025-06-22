/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:04:32 by yael-maa          #+#    #+#             */
/*   Updated: 2025/06/18 22:09:56 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*var_name(char *content, int *index, int *end)
{
	char	*var_name;
	int		i;
	int		j;

	i = *index + 1;
	while (content[i] &&  !ft_isspace(content[i]) && content[i] != '"' && content[i] != '\'')
		i++;
	var_name = malloc(i + 1);
	if (!var_name)
		return (write(2, "Memory Error\n", 13), NULL);
	i = 0;
	j = *index + 1;
	while (content[j] && !ft_isspace(content[j]) && content[j] != '"' && content[j] != '\'')
	{
		var_name[i] = content[j];
		i++;
		j++;
	}
	(*end) = j;
	var_name[i] = '\0';
	return (var_name);
}

int		var_len(char *str, int *len)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (*len == i)
		return (1);
	return (0);
}

char	*var_value(char *var_name, char **env)
{
	char	*var_value;
	int		i;
	int		j;
	int		len;

	i = 0;
	var_value = NULL;
	len = ft_strlen(var_name);
	while (env[i])
	{
		if (var_len(env[i], &len) && !ft_strncmp(var_name, env[i], ft_strlen(var_name) - 1))
		{
			if (env[i][ft_strlen(var_name)] && env[i][ft_strlen(var_name)] == '=')
			{
				var_value = malloc(ft_strlen(env[i]) - ft_strlen(var_name));
				if (!var_value)
					return (write(2, "Memory Error\n", 13), NULL);
				len = ft_strlen(var_name) + 1;
				j = 0;
				while (env[i][len])
				{
					var_value[j] = env[i][len];
					len++;
					j++;
				}
				var_value[j] = '\0';
				break ;
			}
		}
		i++;
	}
	return (var_value);
}

// int	to_expand(t_cmd *cmd)
// {
// 	int	i;

// 	i = -1;
// 	while (cmd->cmd[++i])
// 	{
// 		if (cmd->cmd[i] == "$" && cmd->cmd[i + 1])
// 			return (1);
// 	}
// 	return (0);
// }

int	found_var(char **env, char *var_name)
{
	int	i;
	int lenght;
	i = 0;
	lenght = ft_strlen(var_name);
	while (env[i])
	{
		if (!strncmp(var_name, env[i], lenght) && var_len(env[i], &lenght))
			return (1);
		i++;
	}
	return (0);
}

char	*bef_param(char *cmd , int *index)
{
	char	*bef;
	int		i;
	// int		j;
	
	// i = 0;
	// while (cmd[i] != '$')
	// 	i++;
	bef = malloc((*index) + 1);
	if (!bef)
		return (write(2, "Memory Error\n", 13), NULL);
	i = -1;
	// j = *index;
	while ((++i) < *index)
		bef[i] = cmd[i];
	bef[i] = '\0';
	return (bef);
}

char	*simple_join(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s3)
		return (write(2, "Memory Error\n", 13), NULL);
	i = -1;
	while (s1[++i])
		s3[i] = s1[i];
	j = 0;
	while (s2[j])
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[i + j] = '\0';
	return (s3);
}

// char	*cmd_left(char *cmd, int *start)
// {
// 	char	*left;
// 	int		i;

// 	left = malloc(ft_strlen(cmd) - (*start) + 2);
// 	if (!left)
// 		return (write(2, "Memory Error\n", 13), NULL);
// 	i = 0;
// 	while (cmd[(*start)])
// 	{
// 		left[i]cmd[*start]; 
// 	}	
// }

void	expansion(t_cmd *cmd, char **env)
{
	t_cmd	*tmp;
	char	*par_name;
	char	*bef_var;
	char	*par_value;
	char	*expanded;
	int		index;
	int		i;

	// cmd->f = 0;
	tmp = cmd;
	while (tmp)
	{
		tmp->f = 0;
		if (tmp->type == CMD)
		{
			i = 0;
			while (cmd->cmd[i])
			{
				if (cmd->cmd[i] == '"' && cmd->f >=0)
					cmd->f++;
				else if (cmd->cmd[i] == '\'' && cmd->f <= 0)
					cmd->f--;
				if (cmd->cmd[i] == '$')
				{
					par_name = var_name(cmd->cmd, &i, &index);
					if (cmd->f > -1)
					{
						bef_var = bef_param(cmd->cmd, &i);
						if (!found_var(env, par_name))
							par_value = ft_strdup(" ");
						else
							par_value = var_value(par_name, env);
						expanded = simple_join(bef_var, par_value);
						cmd->cmd = simple_join(expanded, &cmd->cmd[index]);
					}
				}
				if (cmd->f == -2 || cmd->f == 2)
					cmd->f = 0;
				i++;
			}	
		}
		// free(par_name);
		// free(bef_var);
		// free(par_value);
		// free(expanded);
		tmp = tmp->next;
	}
}

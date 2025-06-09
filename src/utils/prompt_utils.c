/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:43:54 by yael-maa          #+#    #+#             */
/*   Updated: 2025/05/20 22:44:16 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_break(char *prompt)
{
	int	i;

	if (!prompt)
		return (0);
	i = 0;
	while (ft_isspace(prompt[i]))
		i++;
	if (prompt[i] && !ft_strncmp("exit", &prompt[i], 4))
	{
		i += 4;
		while (ft_isspace(prompt[i]))
			i++;
		if (!prompt[i])
			return (0);
	}
	return (1);
}

int	finish_prompt(char *prompt)
{
	if (!ft_break(prompt))
	{
		if (prompt)
			free(prompt);
		return (0);
	}
	return (1);
}

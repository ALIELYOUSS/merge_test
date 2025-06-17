/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alel-you <alel-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 23:04:42 by alel-you          #+#    #+#             */
/*   Updated: 2025/06/17 23:28:14 by alel-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int    herdoc_handler(char *delimiter)
{
    int     pipe_ends[2];
    char    *input;
    int     line_len;

    input = NULL;
    line_len = 0;
    if (pipe(pipe_ends) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        ft_putchar_fd(1, '<');
        input = get_next_line(0);
        if (!input)
            break ;
        line_len = ft_strlen(input);
        if (line_len != 0 && input[line_len - 1] == '\n')
            input[line_len - 1] = '\0';
        if (!ft_strncmp(input, delimiter, ft_strlen(input)))
        {
            free(input);
            break ;
        }
        write(pipe_ends[1], input, line_len);
        write(pipe_ends[1], "\n", 1);
        free(input);
    }
    close(pipe_ends[1]);
    return (pipe_ends[0]);
}
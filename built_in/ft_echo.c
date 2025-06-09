#include "../inc/minishell.h"

int is_flag(char *str)
{
    int flag;
    int i;

    i = 0;
    flag = 0;
    if (str[0] == '-') {
        while(str[++i])
        {
            if (str[i] != 'n')
                return (flag);
        }
        flag = 1;
    }
    return (flag);
}

void ft_echo(char **str)
{
    int i;
    int flag;

    i = 1;
    flag = is_flag(str[1]);
    if (td_len(str) > 1 && flag == 1)
        i++;
    while (str[i])
    {
        ft_putstr_fd(str[i], 1);
        if (str[i + 1])
            ft_putchar_fd(' ', 1);
        i++;
    }
    if (flag == 0)
        ft_putchar_fd('\n', 1);
}

// hhhhh
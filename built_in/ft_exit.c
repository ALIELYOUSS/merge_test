#include "../inc/minishell.h"

void    ft_exit(t_env *env)
{
    t_env *head;
    t_env *tmp;

    head = env;
    while (head != NULL)
    {
        tmp = head->next;
        free(head);
        head = tmp;
        if (head == NULL)
            break;
        head = head->next;
    }
    free(head);
    ft_putstr_fd("exit\n", 1);    
    exit(0);
}
#include "../inc/minishell.h"

void    ft_exit(t_env *env)
{
    t_env *head;
    t_env *tmp;

    head = env;
    while (head)
    {
        tmp = head->next;
        free(head);
        head = tmp;
        head = head->next;
    }
    printf("exit\n");
    exit(0);
}
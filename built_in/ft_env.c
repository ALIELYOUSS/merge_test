#include "../inc/minishell.h"

void ft_env(t_env *env)
{
    t_env *current;

    current = env;
    while (current)
    {
        if (current->value)
            printf("%s=%s\n", current->key, current->value);
        else
            printf("%s\n", current->key);
        current = current->next;
    }
}
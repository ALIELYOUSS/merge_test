#include "../inc/minishell.h"

t_env   *sort_env(t_env *env_list)
{
    t_env   *sorted_list;
    t_env   *tmp;
    char    *tmp_key;
    char    *tmp_value;

    tmp = env_list;
    sorted_list = malloc(sizeof(env_list));
    if (!sorted_list)
        error_msg("malloc");
    while (tmp)
    {
        if (tmp->key)
        {
            if (ft_strncmp(tmp->key, tmp->next->key, 1) > 0)
            {
                tmp_key = tmp->key;
                tmp_key = tmp->next->key;
                tmp->next->key = tmp_key;
                if (tmp->value)
                {
                    tmp_value = tmp->value;
                    tmp->value = tmp->next->value;
                    tmp->next->value = tmp_value;
                }
                continue ;
            }
        }
        tmp = tmp->next;
    }
    sorted_list = tmp;
    return (sorted_list);
}

void    print_export(t_env *export)
{
    t_env *tmp;

    tmp = export;
    while (tmp)
    {
        if (tmp->key)
            printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}

 /*
    1 ->if there is no arguments :  sort_env and print it
    2 -> split with spaces and check each one of them
    3 -> store the key and value after spliting(substr from start to pos of = and from pos of = +1 to len of str) with =
    4 -> check if the key already exist in the list of env if its true change old value with new one else add new node into the list
    5 -> if the key is empty show error 
    6-> if the value is empty create a node with empty value;
 */

int find_char(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (0);
}

void    ft_export(char *prompt, t_env **env_list)
{
    char    **export_args;
    char    *val;
    char    *key;
    int     i;
    
    i = 1;
    val = NULL;
    key = NULL;
    export_args = ft_split(prompt, ' ');
    if (!export_args)
        error_msg("split");
    if (td_len(export_args) == 1)
        print_export(*env_list);
    else
    {
        while (export_args[i])
        {
            if (ft_strchr(export_args[i], '='))
            {
                key = ft_substr(export_args[i], \
                    0 , find_char(export_args[i], '='));
                val = ft_substr(export_args[i], \
                    find_char(export_args[i], '=') + 1, ft_strlen(export_args[i]));
            }
        printf("%s=%s\n", key, val);
        i++;
        }
    }
}
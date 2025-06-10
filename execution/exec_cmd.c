#include "../inc/minishell.h"

int    execution(t_cmd *cmd_list, char **env)
{
    t_cmd   *tmp;
    t_env   *env_list; 
    pid_t    i;
    int      status;

    tmp = cmd_list;
    env_list = fill_env_list(env);
    if (!env_list)
        return (-1);
    i = fork();
    if (!i)
    {
        if (tmp && tmp->type == CMD && tmp->cmd && is_builtin(tmp->cmd))
            handle_builtin(tmp->cmd, env_list);
        while (tmp)
        {
            if (tmp->type == OUT || tmp->type ==IN || 
                tmp->type == APP || tmp->type == HRDOC)
                handel_redect(tmp);
            if (tmp->type == CMD && tmp->cmd)
            {
                if (!is_builtin(tmp->cmd) && exec(tmp->cmd, env_list) == -1)
                    exit(EXIT_FAILURE);
            }
            tmp = tmp->next;
        }
        exit(EXIT_SUCCESS);
    }
    waitpid(i, &status, 0);
    return (0);
}
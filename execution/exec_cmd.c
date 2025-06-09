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
    if (tmp && tmp->type == CMD && tmp->cmd && is_builtin(tmp->cmd))
    {
        handle_builtin(tmp->cmd, env_list);
        return (0);
    }
    
    i = fork();
    if (!i)
    {
        while (tmp)
        {
            // if (tmp->redir->type == OUT || tmp->redir->type ==IN || 
            //     tmp->redir->type == APP || tmp->redir->type == HRDOC)
            //     handel_redect(tmp);
            // printf("%d\n", tmp->type);
            if (tmp->type == CMD && tmp->cmd)
            {
                if (is_builtin(tmp->cmd))
                    handle_builtin(tmp->cmd, env_list);
                else if (!is_builtin(tmp->cmd) && exec(tmp->cmd, env_list) == -1)
                    exit(EXIT_FAILURE);
            }
            tmp = tmp->next;
        }
        exit(EXIT_SUCCESS);
    }
    waitpid(i, &status, 0);
    return (0);
}
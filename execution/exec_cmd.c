#include "../inc/minishell.h"

int    execution(t_cmd *cmd_list, char **env)
{
    t_cmd   *tmp;
    t_env   *env_list; 

    tmp = cmd_list;
    env_list = fill_env_list(env);
    if (!env_list)
        return (-1);
    pid_t i = fork();
    if(!i)
    {
        while (tmp)
        {
            if (tmp->redir->type == OUT || tmp->redir->type ==IN || 
                tmp->redir->type == APP || tmp->redir->type == HRDOC)
                handel_redect(tmp);
            else if (tmp->type == CMD)
            {
                // set_fils();///change 1 0 out .... to the redic file
                if (is_builtin(tmp->cmd))
                {
                    handle_builtin(tmp->cmd, env_list);
                    return (0);
                }
                else if (exec(tmp->cmd, env_list) == -1)
                    return (-1);
            }
        }
    }
    else
        return (-1);
    waitpid(i, NULL, 0);
    return (0);
}
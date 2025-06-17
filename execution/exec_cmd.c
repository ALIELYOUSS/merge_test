#include "../inc/minishell.h"

void handle_pipe(t_cmd *cmd_list, t_env *env_list, char **env)
{
    t_cmd   *tmp;
    int     *pipe_fds;
    pid_t   *children;
    int     num_cmds;
    int     i;
    int     j;
    int     flag;
    
    i = 0;
    j = -1;
    flag = -1;
    tmp = cmd_list;
    num_cmds = pipe_counter(cmd_list) + 1;
    children = malloc(sizeof(pid_t) * num_cmds);
    pipe_fds = malloc(sizeof(int) * (2 * (num_cmds)));
    if (!children || !pipe_fds)
        error_msg("malloc");
    while (++j < num_cmds - 1)
    {
        if (pipe(pipe_fds + j * 2) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }
    while (tmp)
    {
        if (tmp->type == HRDOC)
            flag = 0;
        if (tmp->cmd == NULL)
            tmp = tmp->next;
        children[i] = fork();
        if (children[i] < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (children[i] == 0)
        {
            if (i > 0 && flag)
                dup2(pipe_fds[(i - 1) * 2], 0);
            else if (!flag)
            {

            }
            if (tmp->next)
                dup2(pipe_fds[i * 2 + 1], 1);
            j = -1;
            while (++j < 2 * (num_cmds - 1))
                close(pipe_fds[j]);
            if (!is_builtin(tmp->cmd))
                exec(tmp->cmd, env_list, env);
            else
                handle_builtin(tmp->cmd, env_list);
            
            exit(EXIT_FAILURE);
        }
        tmp = tmp->next;
        i++;
    }
    j = -1;
    while (++j < 2 * (num_cmds - 1))
        close(pipe_fds[j]);
    j = -1;
    while (++j < num_cmds)
        waitpid(children[j], NULL, 0);
}

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
        if (tmp && tmp->type == CMD && pipe_counter(cmd_list) > 0)
        {
            handle_pipe(cmd_list, env_list, env);
            exit(EXIT_SUCCESS);
        }
        else if (tmp && tmp->type == CMD && tmp->cmd && is_builtin(tmp->cmd))
        {
            puts("here");
            handle_builtin(tmp->cmd, env_list);
        }
        while (tmp)
        {
            if (tmp->type == OUT || tmp->type ==IN || tmp->type == APP || tmp->type == HRDOC)
                handel_redect(tmp);
            else if (!is_builtin(tmp->cmd))
            {
                exec(tmp->cmd, env_list, env);
                exit(EXIT_FAILURE);
            }
            tmp = tmp->next;
        }
        exit(EXIT_SUCCESS);
    }
    waitpid(i, &status, 0);
    return (0);
}

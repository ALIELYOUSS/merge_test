#include "../inc/minishell.h"

void    handle_pipe(t_cmd *cmd_list, t_env *env)
{
    int     pipe_ends[2];
    pid_t   children[pipe_counter(cmd_list)];
    t_cmd   *tmp;
    int     i;
    int     prev_fd;

    tmp = cmd_list;
    if (!cmd_list)
        exit(EXIT_FAILURE);
    else if (!pipe(pipe_ends))
        exit(EXIT_FAILURE);
    i = -1;
    prev_fd = -1;
    while (tmp && ++i < pipe_counter(cmd_list))
    {
        if (!pipe(pipe_ends))
            exit(EXIT_FAILURE);
        children[i] = fork();
        if (!children[i])
        {
            if (prev_fd != -1)
            {
                dup2(prev_fd, 0);
                close(prev_fd);
            }
            if (tmp->next)
            {
                dup2(pipe_ends[1], 1);
                close(pipe_ends[1]);
            }
            exec(tmp->cmd, env);
        }
        else
            exit(EXIT_FAILURE);
    }
    i = -1;
    while (++i < pipe_counter(cmd_list))
        waitpid(children[i], NULL, 0);
    close(pipe_ends[0]);
    close(pipe_ends[1]);
    prev_fd = pipe_ends[0];
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
    // printf("%d\n", pipe_counter(cmd_list));
    // exit(0);
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
            if (tmp && tmp->type == CMD && pipe_counter(cmd_list) > 0)
            {
                handle_pipe(cmd_list, env_list);
                exit(EXIT_SUCCESS);
            }
            if (!is_builtin(tmp->cmd) && exec(tmp->cmd, env_list) == -1)
                    exit(EXIT_FAILURE);
            tmp = tmp->next;
        }
        exit(EXIT_SUCCESS);
    }
    waitpid(i, &status, 0);
    return (0);
}
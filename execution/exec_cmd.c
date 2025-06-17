#include "../inc/minishell.h"

int *init_pipe_ends(int pipe_num)
{
    int x;
    int *pipe_fds;

    x = -1;
    pipe_fds = malloc((pipe_num - 1) * 2);
    if (!pipe_fds)
        return (NULL);
    while (++x < pipe_num + 1)
    {
        if (pipe(pipe_fds + x *2) == -1)
            return (NULL);
    }
    return (pipe_fds);
}

void handle_pipe(t_cmd *cmd_list, t_env *env_list, char **env)
{
    int     num_cmds;
    pid_t   *children;
    t_cmd   *tmp;
    int     *pipe_ends;
    int     i;
    int     j;

    i = 0;
    j = -1;
    tmp = cmd_list;
    num_cmds = pipe_counter(cmd_list) + 1;
    pipe_ends = init_pipe_ends(num_cmds);
    children = malloc(sizeof(pid_t) * num_cmds);
    if (!pipe_ends)
        error_msg("pipe");
    else if (!children)
        error_msg("malloc");
    while (tmp)
    {
        if (tmp->cmd == NULL)
            tmp = tmp->next;
        children[i] = fork();
        if (children[i] < 0)
            error_msg("fork");
        if (children[i] == 0)
        {
            if (i > 0)
                dup2(pipe_ends[(i - 1) * 2], 0);
            if (tmp->next)
                dup2(pipe_ends[i * 2 + 1], 1);
            j = -1;
            while (++j < 2 * (num_cmds - 1))
                close(pipe_ends[j]);
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
        close(pipe_ends[j]);
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
        if (tmp && pipe_counter(cmd_list) > 0)
        {
            handle_pipe(cmd_list, env_list, env);
            exit(EXIT_SUCCESS);
        }
        else if (tmp && tmp->type == CMD && tmp->cmd && is_builtin(tmp->cmd))
            handle_builtin(tmp->cmd, env_list);
        else if (!is_builtin(tmp->cmd))
            exec(tmp->cmd, env_list, env);
        exit(EXIT_SUCCESS);
    }
    waitpid(i, &status, 0);
    return (0);
}

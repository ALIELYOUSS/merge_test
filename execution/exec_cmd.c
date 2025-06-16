#include "../inc/minishell.h"


// void handle_pipe(t_cmd *cmd_list, t_env *env)
// {
//     int n = pipe_counter(cmd_list);
//     int pipe_fds[2 * n];
//     pid_t children[n + 1];
//     t_cmd *tmp = cmd_list;

//     for (int i = 0; i < n; i++)
//         if (pipe(pipe_fds + i * 2) == -1)
//             perror("pipe"), exit(EXIT_FAILURE);

//     int i = 0;
//     while (tmp)
//     {
//         children[i] = fork();
//         if (children[i] < 0)
//             perror("fork"), exit(EXIT_FAILURE);

//         if (children[i] == 0) // Child
//         {
//             // Redirect input
//             if (i > 0)
//                 dup2(pipe_fds[(i - 1) * 2], 0);
//             // Redirect output
//             if (tmp->next)
//                 dup2(pipe_fds[i * 2 + 1], 1);

//             // Close all pipe ends in child
//             for (int j = 0; j < 2 * n; j++)
//                 close(pipe_fds[j]);

//             exec(tmp->cmd, env);
//             perror("exec failed");
//             exit(EXIT_FAILURE);
//         }
//         tmp = tmp->next;
//         i++;
//     }

//     // Close all pipe ends in parent
//     for (int j = 0; j < 2 * n; j++)
//         close(pipe_fds[j]);

//     // Wait for all children
//     for (int j = 0; j < i; j++)
//         waitpid(children[j], NULL, 0);
// }


void handle_pipe(t_cmd *cmd_list, t_env *env_list, char **env)
{
    int num_cmds = pipe_counter(cmd_list) + 1;
    int pipe_fds[2 * (num_cmds - 1)];
    pid_t children[num_cmds];
    t_cmd *tmp = cmd_list;
    int i = 0;
    int j = -1;

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
            if (i > 0)
                dup2(pipe_fds[(i - 1) * 2], 0);
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
            handle_builtin(tmp->cmd, env_list);
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
    // void    handle_pipe(t_cmd *cmd_list, t_env *env)
    // {
    //     int pipe_ends[pipe_counter(cmd_list) * 2];
    //     int prev_fd = -1;
    //     pid_t children[pipe_counter(cmd_list)];
    //     t_cmd *tmp = cmd_list;
    //     int i = 0;
    //     while (tmp)
    //     {
    //         if (tmp->next && pipe(pipe_ends + i * 2) != -1)
    //             exit(EXIT_FAILURE);
    //         children[i] = fork();
    //         if (children[i] == -1)
    //             exit(EXIT_FAILURE);
    //         else if (children[i] == 0)
    //         {
    //             if (prev_fd != -1)
    //             {
    //                 if (dup2(prev_fd, 0) == -1)
    //                     exit(0);
    //             }
    //             if (dup2(pipe_ends[0], 0) == -1 || dup2(pipe_ends[1], 1) == -1)
    //                 exit(EXIT_FAILURE);
    //             printf("here\n");
    //             exec(tmp->cmd, env);
    //             printf("here\n");
    //         }
    //         i++;
    //         tmp = tmp->next;
    //     }
    // }
    
    //     while (tmp)
    //     {
    //         int is_last = (tmp->next == NULL);
    //         // Only create a pipe if there is a next command
    //         if (!is_last && pipe(pipe_ends) == -1)
    //         {
    //             perror("pipe");
    //             exit(EXIT_FAILURE);
    //         }
    //         children[i] = fork();
    //         if (children[i] < 0)
    //         {
    //             perror("fork");
    //             exit(EXIT_FAILURE);
    //         }
    //         if (children[i] == 0) // Child process
    //         {
    //             if (prev_fd != -1)
    //             {
    //                 dup2(prev_fd, 0);
    //                 close(prev_fd);
    //             }
    //             if (!is_last)
    //             {
    //                 close(pipe_ends[0]); // Close unused read end
    //                 dup2(pipe_ends[1], 1);
    //                 close(pipe_ends[1]);
    //             }
    //             exec(tmp->cmd, env);
    //             perror("exec");
    //             exit(EXIT_FAILURE);
    //         }
    //         // Parent process
    //         if (prev_fd != -1)
    //         {
    //             close(prev_fd); // Close previous read end
    //             prev_fd = -1;
    //         }
    //         if (!is_last)
    //         {
    //             close(pipe_ends[1]); // Close write end in parent
    //             prev_fd = pipe_ends[0]; // Save read end for next command
    //         }
    //         tmp = tmp->next;
    //         i++;
    //     }
    //     // Wait for all children
    //     for (int j = 0; j < i; j++)
    //         waitpid(children[j], NULL, 0);
    // }
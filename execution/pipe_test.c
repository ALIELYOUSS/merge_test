// void    exec_cmd_list(t_cmd *cmd_list, char **env)
// {
//     t_cmd   *tmp;
//     t_env   *env_list;
//     pid_t   child;

//     tmp = cmd_list;
//     env_list = NULL;
//     if (env)
//         env_list = fill_env_list(env);
//     if (!cmd_list || !env_list)
//         exit(EXIT_FAILURE);
//     child = fork();
//     if (child == -1)
//         error_msg("fork");
//     if (!child)
//     {
//         if (tmp->type == OUT || tmp->type ==IN || tmp->type == APP || tmp->type == HRDOC)
//             handel_redect(cmd_list);
//         else if (tmp && tmp->cmd && pipe_counter(cmd_list) > 0)
//         {

//         }
//         else
//     }
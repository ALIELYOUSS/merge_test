#include "../inc/minishell.h"

char    *add_cmd_to_path(char *path, char *cmd)
{
    char *path_slash;
    char *ret;

    path_slash = ft_strjoin(path, "/");
    if (!path_slash)
        return (NULL);
    ret = ft_strjoin(path_slash, cmd);
    if (!ret)
        return (NULL);
    free(path_slash);
    return (ret);
}

char    *return_path(char *cmd, t_env *env_list)
{
    char    **paths;
    char    *path_list;
    char    *path_tester;
    int      i;

    i = 0;
    path_tester = NULL;
    path_list = env_path(env_list, "PATH");
    if (!path_list)
        error_msg("path not found in env");
    paths = ft_split(path_list, ':');
    if (!paths || !paths[0])
        return (NULL);
    while (paths[i])
    {
        path_tester = add_cmd_to_path(paths[i], cmd);
        if (!path_tester)
            return (NULL);
        else if (!access(path_tester, X_OK))
        {
            free_td(paths);
            return (path_tester);
        }
        free(path_tester);
        i++;
    }
    free_td(paths);
    return (NULL);
}

char *remove_cotes(char *arg)
{
    char    *ret;
    int     i;
    int     x;

    if (!arg)
        return (NULL);
    ret = malloc((ft_strlen(arg) - 2) + 1);
    if (!ret)
        return (NULL);
    i = 0;
    x = 0;
    while (arg[i])
    {
        if (arg[i] != '"')
        {
            ret[x] = arg[i];
            x++;
        }
        i++;
    }
    free(arg);
    ret[x] = '\0';
    return (ret);
}

void    exec(char *prompt, t_env *env, char **env_p)
{
    char *cmd_path;
    char **tokens;

    cmd_path = NULL;
    if (ft_strchr(prompt, '"'))
        prompt = remove_cotes(prompt);
    tokens = ft_split(prompt, ' ');
    if (!tokens)
       error_msg("split");
    cmd_path = return_path(tokens[0], env);
    if (!cmd_path)
    {
        if (!ft_strncmp(tokens[0], "./minishell", ft_strlen("./minishell")))
        {
            
            if (execve("./minishell", tokens, env_p) == -1) {
                perror("execve failed");
                exit(EXIT_FAILURE);
            }
            free_td(tokens);
            exit(EXIT_FAILURE);
        }
        else
        {
            free_td(tokens);
            error_msg("commandnot found");
        }
    }
    else
    {
        if (execve(cmd_path, tokens, env_p) == -1) {
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
        free(cmd_path);
        error_msg("execve");
    }
}

void    free_td(char **str)
{
    int i;

    i = -1;
    while (str[++i])
        free(str[i]);
}

void    handle_echo(char *prompt)
{
    char    **splited;

    if (ft_strncmp(prompt, "echo", ft_strlen(prompt)) == 0)
        return ;
    splited = ft_split(prompt, ' ');
    if (!splited)
        return ;
    ft_echo(splited);
    free_td(splited);
}

void    handle_builtin(char *prompt, t_env *env)
{
    if (!ft_strncmp(prompt, "exit", 4))
        ft_exit(env);
    else if (!ft_strncmp(prompt, "pwd", 3))
        ft_pwd();
    else if (!ft_strncmp(prompt, "env", 3))
        ft_env(env);
    else if (!ft_strncmp(prompt, "echo", 4))
        handle_echo(prompt);
    else if (!ft_strncmp(prompt, "cd", 2))
        ft_cd(prompt, env);
}

int is_builtin(char *prompt)
{
    if (!ft_strncmp(prompt, "echo", 4))
        return (1);
    else if (!ft_strncmp(prompt, "cd", 2))
        return (1);
    else if (!ft_strncmp(prompt, "env", 3))
        return (1);
    else if (!ft_strncmp(prompt, "exit", 4))
        return (1);
    else if (!ft_strncmp(prompt, "export", 6))
        return (1);
    else if (!ft_strncmp(prompt, "pwd", 3))
        return (1);
    else if (!ft_strncmp(prompt, "unset", 5))
        return (1);
    return (0);
}

int pipe_counter(t_cmd *list)
{
    int     count;
    t_cmd   *tmp;

    count = 0;
    tmp = list;
    while (tmp)
    {
        if (tmp->type == PIPE)
            count++;
        tmp = tmp->next;
    }
    return (count);
}

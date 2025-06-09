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

int    exec(char *prompt, t_env *env)
{
    int i;
    char *path;
    char **paths;
    char *cmd_path;
    char **tokens;

    i = 0;
    tokens = ft_split(prompt, ' ');
    if (!tokens)
        return (-1);
    path = NULL;
    path = env_path(env, "PATH");
    paths = ft_split(path, ':');
    if (!paths || !path)
        return (-1);
    while (paths[i])
    {
        cmd_path = add_cmd_to_path(paths[i], tokens[0]);
        if (!access(cmd_path, X_OK))
        {
            execve(cmd_path, tokens, NULL);
            free(cmd_path);
        }
        i++;
    }
    i = 0;
    while (paths[i++])
        free(paths[i]);
    free(paths);
    return (0);
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
        ft_cd(&prompt, env);
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
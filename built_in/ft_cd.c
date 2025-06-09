#include "../inc/minishell.h"

static void error_chdir(int chdir_return)
{
    if (chdir_return != 0)
        perror("chdir: ");
}

void    ft_cd(char *prompt, t_env *env)
{
    char    *path;
    char    **paths;

    path = NULL;
    paths = ft_split(prompt, ' ');
    if (!paths)
        return;
    if (paths[1] == NULL || ft_strncmp(paths[1], "", 1) == 0)
    {
        path = env_path(env, "HOME");
        if (!path)
            error_msg("cd: HOME not set");
        error_chdir(chdir(path));
        if (path)
            free(path);
    }
    else
        error_chdir(chdir(paths[1]));
    int i = 0;
    while (paths[i])
    {
        free(paths[i]);
        i++;
    }
    free(paths);
}
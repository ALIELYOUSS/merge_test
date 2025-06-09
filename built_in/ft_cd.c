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
    printf("%s||||||\n", paths[1]);
    if (ft_strncmp(prompt, "cd", ft_strlen(prompt)) == 0)
    {
        path = env_path(env, "HOME");
        if (!path)
            error_msg("cd: HOME not set");
        error_chdir(chdir(path));
        free(path);
    }
    else
        error_chdir(chdir(paths[1]));
}
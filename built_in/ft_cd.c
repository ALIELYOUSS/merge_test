#include "../inc/minishell.h"

static void error_chdir(int chdir_return)
{
    if (chdir_return != 0)
        perror("chdir: ");
}

void    ft_cd(char **prompt, t_env *env)
{
    char    *path;

    path = NULL;
    if (ft_strncmp(prompt[0], "cd", ft_strlen(prompt[0])) == 0)
    {
        path = env_path(env, "HOME");
        if (!path)
            error_msg("cd: HOME not set");
        error_chdir(chdir(path));
        free(path);
        return ;
    }
   error_chdir(chdir(prompt[1]));
}
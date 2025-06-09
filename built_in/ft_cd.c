#include "../inc/minishell.h"

static void error_chdir(int chdir_return)
{
    if (chdir_return != 0)
        perror("chdir: ");
}

void    ft_cd(char *prompt, t_env *env)
{
    char    *path;

    path = NULL;
    if (ft_strncmp(prompt, "cd", ft_strlen(prompt)) == 0)
    {
        path = env_path(env, "HOME");
        if (!path)
            return ;
        error_chdir(chdir(path));
        free(path);
        return ;
    }
    path = ft_strdup(prompt + 3);
    if (!path)
        return ;
   error_chdir(chdir(path));
   free(path);
}
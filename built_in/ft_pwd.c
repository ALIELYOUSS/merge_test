#include "../inc/minishell.h"

void ft_pwd()
{
    char    *pwd;
    
    pwd = getcwd(NULL, 0);
    if (pwd)
    {
        printf("%s\n", pwd);
        free(pwd);
    }
    else
    {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
}

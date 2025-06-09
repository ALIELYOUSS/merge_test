// #include "../inc/minishell.h"

// static t_env *help_export(t_env *env)
// {
//     t_env   *tmp;
//     char    *var;

//     tmp = malloc(sizeof(t_env));
//     tmp = env;
//     while (tmp)
//     {
//         tmp->key = ft_strjoin("declare -x ", tmp->key);
//         tmp = tmp->next;
//     }
//     return (tmp);
// }

// void    print_export(t_env *export)
// {
//     t_env *tmp;

//     tmp = export;
//     while (tmp)
//     {
//         printf("%s=%s\n", tmp->key, tmp->value);
//         tmp = tmp->next;
//     }
// }

// // uncomplitd work

// // void    hlp_adder_to_env(char *prompt, t_env *env)
// // {
// //     t_env   *node;
// //     t_env   *tmp;
// //     int     i;
// //     int     x;
// //     int     flag;

// //     tmp = env;
// //     node = malloc(sizeof(node));
// //     while (tmp)
// //         tmp = tmp->next;
// //     tmp->next = node;
// //     node->next = NULL;
// //     i = 0;
// //     flag = 0;
// //     while (prompt[i] != '=')
// //         node->key = prompt[i++];
// //     if (prompt[i] == '=')
// //     {
// //         flag = 1;
// //         i++;
// //     }
// //     while ()
// //     {
// //         node->value = prompt[i];
// //     }
// // }

// // void    add_to_export_list(char *prompt, t_env *export)
// // {

// // }

// void    add_to_export(char **splited, t_env *env, t_env *export, char *prompt)
// {
//     int i;

//     i = 1;
//     while (splited[i])
//     {
//         if (ft_strrchr(splited[i], '='))
//         {
//             hlp_adder_to_env(prompt, env);
//             return ;
//         }
//         i++;    
//     }
//     add_to_export_list(, export);
// }

// void    ft_export(char *prompt, t_env *env)
// {
//     char    **str;
//     int     i;

//     t_env   *export;
//     export = help_export(env);
//     if (ft_strlen(prompt) > 6)
//     {
//         str = ft_split(prompt, ' ');
//         if (!str)
//             return ;
//         add_to_export(str, env, export, prompt);
//     }
//     print_export(export);
// }

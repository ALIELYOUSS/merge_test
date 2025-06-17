# ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/wait.h>
#include "../get_next_line/get_next_line.h"



typedef enum e_type
{
	WORD,
	OUT,
	IN,
	APP,
	HRDOC,
	AND,
	OR,
	PIPE,
	LP,
	RP,
	CMD,
}	t_type;

typedef struct s_tokens
{
	t_type				type;
	char				*content;
	struct s_tokens		*next;
}	t_tokens;

typedef struct s_list
{
	t_tokens	*head;
	t_tokens	*tail;
	int			size;
}	t_list;

typedef struct s_redir
{
	t_type			type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	t_type			type;
	char			*cmd;
	t_redir			*redir;
	int 			in;
	int 			out;
	// struct s_cmd	*r_child;
	// struct s_cmd	*l_child;
	struct s_cmd	*next;
}	t_cmd;

typedef struct env_s
{
    char *key;
    char *value;
    struct env_s *next;
}   t_env;

typedef struct s_garbage
{
	void					*ptr;
	t_list					*tokens;
	struct s_garbage		*next;
}	t_garbage;

// libft split struct
typedef struct s_variables
{
	unsigned int	i;
	unsigned int	x;
	unsigned int	n;
	unsigned int	len;
	unsigned int	words;
	char			**sp;
}	t_var;

// libft_utils
int 		pipe_counter(t_cmd *list);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
char		*ft_strchr( char *s, int c);
char		**ft_split(char *s, char c);
char		*ft_strjoin(char *s1, char *s2);
// built-in
void    	ft_env(t_env *env);
void    	ft_echo(char **str);
void		ft_cd(char *prompt, t_env *env);
void    	ft_exit(t_env *env);
void    	ft_pwd();
// execution
int 		is_builtin(char *prompt);
// int 		is_parent_builtin(char *prompt);
void    	handle_builtin(char *prompt, t_env *env);
void    	error_msg(char *str);
void		handel_redect(t_cmd * cmd);
void    exec(char *prompt, t_env *env, char **env_p);
char		*env_path(t_env *env, char *key);
t_env		*fill_env_list(char **envp);
t_env		*create_env_node( char *var);
int     	td_len(char **str);
void    	free_td(char **str);
int			execution(t_cmd *cmd_list, char **env);
// parsing
int			ft_strlen(char *str);
int			ft_strncmp( char *s1,  char *s2, size_t n);
int			ft_break(char *prompt);
int			ft_isspace(char c);
int			ft_break(char *prompt);
int			finish_prompt(char *prompt);
void		ft_bzero(void *s, size_t n);
void		add_node(t_list *tokens, t_tokens *token);
t_tokens	*create_token(void *content, int t);
char		*get_word(char *str, int *index);
void		found_quotes(char *content, int *i);
int			found_quotes_helper(char *content, int *i, int *tmp, char c);
void		print_list(t_list *tokens);
void		clear_list(t_list *tokens);
void		quotes_syntax_error(void);
int			for_word(char c);
int			delimiter(char *str, char *c);
char		*str_trim(char *str);
void		tokenizer(t_list *tokens, char *content, int *i);
void		redir_and_hrdc(t_list *tokens, char *content, int *i);
void		pipe_and_or(t_list *tokens, char *content, int *i);
void		tokenizer_helper(t_list *tokens, char *content, int *i);
void		garbage_collector(t_garbage **garbage, t_garbage *new);
t_garbage	*ft_lstlast(t_garbage **garbage);
t_garbage	*add_garbage(void *ptr, t_list *tokens);
int			ft_lstsize(t_garbage *garbage);
void		free_garbage(t_garbage *garbage);
void		syntax_error_msg(t_list *tokens);
int			find_token(t_tokens *tokens, t_type type);
int			operator(t_tokens *token);
int			its_token(t_tokens *tokens, t_type type);
t_type		prev_node(t_list *tokens, t_tokens *token);
int			is_redir(t_tokens *token);
int			is_redir(t_tokens *token);
void		syntax_errors(t_list *tokens);
char		*ft_strdup(char *s1);
int			parenthese(t_tokens *token);
int			multi_parenth(t_list *tokens, t_tokens *token, int *flag);
int			parenthese_se(t_list *tokens, t_tokens *token, int	*flag);
int			closed_parenthese(t_tokens *token);
t_cmd		*new_cmd(char *content, t_redir *redir,t_type type);
void		add_cmd(t_cmd **cmd, t_cmd *new);
t_cmd		*new_cmd(char *content, t_redir *redir,t_type type);
t_cmd		*last_cmd(t_cmd **cmd);
char		*join_it(char *s1, char *s2);
void		add_redir(t_cmd **cmd, t_redir *new);
t_redir		*new_redir(char *content, t_type type);
t_redir		*last_redir(t_redir *redir);
t_cmd		*build_cmd(t_list *tokens);
void    	clear_cmd(t_cmd *cmd);
void    	clear_directions(t_redir *redir);

#endif
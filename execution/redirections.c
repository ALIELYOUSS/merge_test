#include "../inc/minishell.h"

void handel_out(t_cmd *cmd)
{
    cmd->out = open(cmd->redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(!cmd->out)
        exit(1);
}
void handel_in(t_cmd *cmd)
{
    cmd->in = open(cmd->redir->file, O_RDONLY | O_CREAT, 0777);
    if(!cmd->in)
        exit(1);
}
void handel_append(t_cmd *cmd)
{
    cmd->out = open(cmd->redir->file, O_WRONLY | O_CREAT| O_APPEND, 0777);
    if(!cmd->in)
        exit(1);
}

void handel_redect(t_cmd * cmd)
{
    if (cmd->type == IN)
            handel_in(cmd);
	else if (cmd->type == OUT)
            handel_out(cmd);
    else if (cmd->type == APP)
            handel_append(cmd);
}


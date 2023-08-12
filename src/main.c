/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:53:51 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/12 15:21:43 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//====================================PARSING=====================================//

// 1) Parse command line

// 2) Build the tree representation 

// 3) Return the root node of the tree

// -------------------------------FUNC PARSING -------------------------------//
// -parsecmd ( ps, es)
// -parsepipe --> parseexec --> parseredir
// -addng null terminator to thr tree recursivly


//====================================Execution====================================//

// 1) get the tree root node

// 2) run the tree recursivle

// -------------------------------FUNC EXECtion -------------------------------//
// - pipe -> fd[2] -> pipe(fd) -> redirect the output of left_subtree to became input of right_subtree
// - redir : close fd of redir struct nd open the file of struct; then call runcmd(redircmd->subcmd)
// - exec : execve


// Parsed command representation
#define EXEC  1
#define REDIR 2
#define PIPE  3

#define MAXARGS 10


typedef struct s_cmd
{
	int	type;
}		t_cmd;

typedef struct s_pipecmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}			t_pipecmd;

typedef struct s_execcmd
{
	int		type;
	char	*args[MAXARGS];
	char	*eargs[MAXARGS];
}			t_execcmd;

typedef struct s_redircmd
{
	int		type;
	char	*file;
	char	*efile;
	int		fd;
	int		mod;
	t_cmd	*subcmd;
}			t_redircmd;

t_cmd	*pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*cmd;

	cmd = (t_pipecmd *)malloc(sizeof(t_pipecmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd   *execcmd(void)
{
    t_execcmd   *cmd;

    cmd = (t_execcmd *)malloc(sizeof(t_execcmd));
    ft_memset(cmd, 0, sizeof(t_execcmd));
    cmd->type = EXEC;
    return ((t_cmd *)cmd);
}

t_cmd   *redircmd(t_cmd *subcmd, char *file, char *efile, int mod, int fd)
{
    t_redircmd  *cmd;

    cmd = (t_redircmd*)malloc(sizeof(t_redircmd));
    cmd->type = REDIR;
    cmd->file = file;
    cmd->efile = efile;
    cmd->mod = mod;
    cmd->fd = fd;
    cmd->subcmd = subcmd;
    return ((t_cmd *)cmd);
}

void    panic(char *s)
{
	perror(s);
	exit(1);
}

int forking()
{
	int	pid;

	pid = fork();
	if (pid == -1)
		panic("fork");
	return (pid);
}

char	whitespaces[] = " \t\n\v\f\r";
char	symbols[] = "<|>";

int	get_next_token(char **ps, char *es, char **q, char **eq)
{
	int		token;
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(whitespaces, *s))
		s++;
	if (q)
		*q = s;
	token = *s;
	if (token == '\0')
	{
		token = '\0';
	}
	else if (token == '|')
	{
		s++;
	}
	else if (token == '>')
	{
		s++;
		if (*s == '>')
		{
			token = '+';
			s++;
		}
	}
	else if (token == '<')
	{
		s++;
		// if (token == '<')
		// {
		// 	token = '#';
		// 	s++;
		// }
	}
	else
	{
		token = 'a';
		while (s < es && !ft_strchr(whitespaces, *s) && !ft_strchr(symbols, *s))
			s++;
	}
	if (eq)
		*eq = s;
	while (s < es && ft_strchr(whitespaces, *s))
		s++;
	*ps = s;
	return (token);
}

int	peek(char **ps, char *es, char *tokens)
{
	char *s;

	s = *ps;
	while (s < es && ft_strchr(whitespaces, *s))
		s++;
	*ps = s;
	
	return (*s && ft_strchr(tokens, *s));
}

t_cmd	*parse_redir(t_cmd *subcmd, char **ps, char *es);
t_cmd *parse_pipe(char **ps, char *es);
t_cmd	*null_terminator(t_cmd *cmd);
t_cmd	*parse_exec(char **ps, char *es);

t_cmd *parse_cmd(char *buf)
{
	char	*ps;
	char	*es;
	t_cmd	*cmd;

	ps  = buf;
	es = ps + ft_strlen(ps);
	cmd = parse_pipe(&ps, es);
	peek(&ps, es, "");
	if (ps != es)
		panic("Syntax Error");
	null_terminator(cmd);
	return (cmd);
}

t_cmd	*null_terminator(t_cmd *cmd)
{
	t_execcmd	*ecmd;
	t_redircmd	*rcmd;
	t_pipecmd	*pcmd;
	int			i;

	if (cmd->type == EXEC)
	{
		i = 0;
		ecmd = (t_execcmd *)cmd;
		while (ecmd->eargs[i])
		{
			*ecmd->eargs[i] = '\0';
			i++;
		}
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		*rcmd->efile = '\0';
		null_terminator(rcmd->subcmd);
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		null_terminator(pcmd->left);
		null_terminator(pcmd->right);
	}
	return(cmd);
}

t_cmd *parse_pipe(char **ps, char *es)
{
	t_cmd *cmd;
	
	cmd = parse_exec(ps, es);
	if (peek(ps, es, "|"))
	{
		get_next_token(ps, es, 0, 0);
		cmd = pipecmd(cmd, parse_pipe(ps, es));
	}	
	return (cmd);
}

t_cmd	*parse_exec(char **ps, char *es)
{
	t_cmd		*cmd;
	t_execcmd	*exec_cmd;
	char		*q;
	char		*eq;
	int			argc;
	int			token;
	
	argc = 0;
	cmd = execcmd();
	exec_cmd = (t_execcmd *)cmd;
	cmd = parse_redir(cmd, ps, es);
	while (!peek(ps, es, "|"))
	{
		token = get_next_token(ps, es, &q, &eq);
		if (token == '\0')
			break ;
		else if (token != 'a')
			panic("Syntax Error");
		exec_cmd->args[argc] = q;
		exec_cmd->eargs[argc] = eq;
		argc++;
		cmd = parse_redir(cmd, ps, es);
	}
	exec_cmd->args[argc] = NULL;
	exec_cmd->eargs[argc] = NULL;
	return (cmd);
}

t_cmd	*parse_redir(t_cmd *subcmd, char **ps, char *es)
{
	char	*q;
	char	*eq;
	int		tok;
	t_cmd	*cmd;

	cmd = subcmd;
	if (peek(ps, es, "<>"))
	{
		tok = get_next_token(ps, es, 0, 0);
		if (get_next_token(ps, es, &q, &eq) != 'a')
			panic("Syntx Error");
		if (tok == '<')
			cmd = redircmd(parse_redir(subcmd, ps, es), q, eq, O_RDONLY, 0);
		else if (tok == '>')
			cmd = redircmd(parse_redir(subcmd, ps, es), q, eq, O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (tok == '+')
			cmd = redircmd(parse_redir(subcmd, ps, es), q, eq, O_WRONLY | O_CREAT | O_APPEND, 1);
	}
	return (cmd);
}


void	display_tree(t_cmd *cmd)
{
	t_execcmd	*ecmd;
	t_redircmd	*rcmd;
	t_pipecmd	*pcmd;

	if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		printf("=======PIPE======\n\n");
		printf("=======Pipe Left======\n");
		display_tree(pcmd->left);
		printf("=======Pipe Right======\n");
		display_tree(pcmd->right);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		printf("=======REDIR======\n");
		printf("The file is : %s\n", rcmd->file);
		printf("The fd is : %d\n", rcmd->fd);
		printf("My subcmd is : \n");
		display_tree(rcmd->subcmd);
	}
	else if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		printf("=========EXEC=======\n");
		printf("The command is : ");
		for (int i = 0; ecmd->args[i]; i++)
		{
			printf("%s ", ecmd->args[i]);
		}
		printf("\n\n");
	}
}

void	run_cmd(t_cmd *cmd)
{
	int	fd[2];
	t_redircmd	*rcmd;
	t_pipecmd	*pcmd;
	t_execcmd	*ecmd;

	if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		pipe(fd);
		if (forking() == 0)
		{
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
			run_cmd(pcmd->left);
		}
		if (forking() == 0)
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			run_cmd(pcmd->right);
		}
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
		wait(NULL);
	}
	else if(cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		close(rcmd->fd);
		if (open(rcmd->file, rcmd->mod, 0644) < 0)
		{
			panic("open");
			exit(1);
		}
		run_cmd(rcmd->subcmd);
	}
	else if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		execvp(ecmd->args[0], ecmd->args);
	}
	exit(0);
}

// int main(int argc, char **argv, char **envp)
int main()
{
    char    *buf;
	t_cmd	*main_tree;
    
    while (1)
    {
        ft_printf("minishell$ ");
        buf = get_next_line(0);
        if (ft_strlen(buf) == 0 || !buf)
            continue;
        if(forking() == 0)
        {
            main_tree = parse_cmd(buf);
			run_cmd(main_tree);
        }
        wait(0);
		free(buf);
        
    }
    exit(0);
}
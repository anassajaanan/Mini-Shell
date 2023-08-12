/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:53:51 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/12 09:44:16 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	int		tok;
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(whitespaces, *s))
		s++;
	if (q)
		*q = s;
	tok = *s;
	if (tok == '\0')
		tok = 0;
	else if (tok == '|')
		s++;
	else if (tok == '>')
	{
		s++;
		if (*s == '>')
		{
			tok = '+';
			s++;
		}
	}
	else if (tok == '<')
		s++;
	else
	{
		tok = 'a';
		while (s < es && !ft_strchr(whitespaces, *s) && !ft_strchr(symbols, *s))
			s++;
	}
	if (eq)
		*eq = s;
	while (s < es && ft_strchr(whitespaces, *s))
		s++;
	*ps = s;
	return (tok);
}

int	peek(char **ps, char *es, char *tok)
{
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(whitespaces, *s))
		s++;
	*ps = s;
	return (*s && ft_strchr(tok, *s));
}

t_cmd	*parseexec(char **ps, char *es);
t_cmd	*parseredir(t_cmd *subcmd, char **ps, char *es);

t_cmd	*parsepipe(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = parseexec(ps, es);
	if (peek(ps, es, "|"))
	{
		get_next_token(ps, es, 0, 0);
		cmd = pipecmd(cmd, parsepipe(ps, es));
	}
	return (cmd);
}

t_cmd	*parseexec(char **ps, char *es)
{
	t_cmd		*ret;
	t_execcmd	*cmd;
	char		*q;
	char		*eq;
	int			argc;
	int			tok;

	ret = execcmd();
	cmd = (t_execcmd *)ret;
	ret = parseredir(ret, ps, es);
	argc = 0;
	while (!peek(ps, es, "|"))
	{
		tok = get_next_token(ps, es, &q, &eq);
		if (tok == '\0')
			break;
		else if (tok != 'a')
			panic("Syntax Error");
		cmd->args[argc] = q;
		cmd->eargs[argc] = eq;
		argc++;
		if (argc >= 9)
			panic("Too many arguments");
		ret = parseredir(ret, ps, es);
	}
	cmd->args[argc] = NULL;
	cmd->eargs[argc] = NULL;
	return (ret);
}

t_cmd	*parseredir(t_cmd *subcmd, char **ps, char *es)
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
		{
			panic("Syntax error : Missing file name after redirection");
		}
		if (tok == '<')
			cmd = redircmd(parseredir(subcmd, ps, es), q, eq, O_RDONLY, 0);
		else if (tok == '>')
			cmd = redircmd(parseredir(subcmd, ps, es), q, eq, O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (tok == '+')
			cmd = redircmd(parseredir(subcmd, ps, es), q, eq, O_WRONLY | O_CREAT | O_APPEND, 1);
	}
	return (cmd);
}

t_cmd	*nullterminate(t_cmd *cmd)
{
	t_pipecmd	*pcmd;
	t_execcmd	*ecmd;
	t_redircmd	*rcmd;

	if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		nullterminate(pcmd->left);
		nullterminate(pcmd->right);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		nullterminate(rcmd->subcmd);
		*rcmd->efile = '\0';
	}
	else if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		int i = 0;
		while (ecmd->args[i])
		{
			*ecmd->eargs[i] = '\0';
			i++;
		}
	}
	return (cmd);
}

t_cmd	*parsecmd(char *buff)
{
	char	*ps;
	char	*es;
	t_cmd	*cmd;

	ps = buff;
	es = ps + ft_strlen(ps);
	cmd = parsepipe(&ps, es);
	peek(&ps, es, "");
	if(ps != es){
		panic("syntax");
	}
	cmd = nullterminate(cmd);
	return (cmd);
}

void	display_tree(t_cmd *cmd)
{
	t_pipecmd	*pcmd;
	t_execcmd	*ecmd;
	t_redircmd	*rcmd;

	if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		printf("\n\n=======PIPE======\n\n");
		printf("\n\n=======PIPE LEFT======\n");
		display_tree(pcmd->left);
		printf("\n\n=======PIPE RIGHT======\n");
		display_tree(pcmd->right);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		printf("=======REDIR========\n");
		printf("file :%s\n", rcmd->file);
		printf("The fd is : %d\n", rcmd->fd);
		printf("subcmd is : \n");
		display_tree(rcmd->subcmd);
	}
	else if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		printf("========EXEC=======\n");
		printf("The command is : ");
		for (int i = 0; ecmd->args[i]; i++)
			printf("%s ", ecmd->args[i]);
		printf("\n\n");
	}
}

// int main(int argc, char **argv, char **envp)
int main()
{
    char    *buff;
    
    while (1)
    {
        ft_printf("minishell$ ");
        buff = get_next_line(0);
        if (ft_strlen(buff) == 0 || !buff)
            continue;
        if(forking() == 0)
        {
            display_tree(parsecmd(buff));
        }
        wait(0);
		free(buff);
        
    }
    exit(0);
}
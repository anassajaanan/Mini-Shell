/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:53:51 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/11 20:48:21 by aajaanan         ###   ########.fr       */
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

int get_next_token(char **ps, char *es, char **q, char **eq)
{
    char    *s;
    int     token;

	s = *ps;
    while (s < es && ft_strchr(whitespaces, *s))
        s++;
    if (q)
        *q = s;
    token = *s;
    if (token == '|')
        s++;
    else if (token == '>')
    {
        s++;
        if (*s == '>')
            token = '+';
    }
    else if (token == '<')
    {
        s++;
        //if (*s == '<')
        //token = '';
    }
    else
    {
        token = 'a';
        while (s < es && !ft_strchr(symbols, *s) && !ft_strchr(whitespaces, *s))
            s++;
    }
    if (eq)
        *eq = s;
    while (s < es && ft_strchr(whitespaces, *s))
        s++;
	*ps = s;
	return (token);
}

int main(int argc, char **argv, char **envp)
{
    char    *buf;
    
    while (1)
    {
        ft_printf("minishell$ ");
        buf = get_next_line(0);
        if (ft_strlen(buf) == 0 || !buf)
            continue;
        if(forking() == 0)
        {
            
            
        }
        wait(0);
        
    }
    exit(0);
}
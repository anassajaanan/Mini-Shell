/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:53:51 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/18 14:20:26 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <time.h>



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
	int		redirection_type;
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

t_cmd   *redircmd(t_cmd *subcmd, char *file, char *efile, int mod, int fd, int redirection_type)
{
    t_redircmd  *cmd;

    cmd = (t_redircmd*)malloc(sizeof(t_redircmd));
    cmd->type = REDIR;
    cmd->file = file;
    cmd->efile = efile;
    cmd->mod = mod;
    cmd->fd = fd;
    cmd->subcmd = subcmd;
	cmd->redirection_type = redirection_type;
    return ((t_cmd *)cmd);
}

void    panic(char *s)
{
	perror(s);
	exit(1);
}

void	panic_exit(int status, char	*s)
{
	perror(s);
	exit(status);
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
		if (*s == '<')
		{
			token = '%';
			s++;
		}
	}
	else if (token == '\'')
	{
		token = 'a';
		s++;
		while (s < es && *s != '\'')
			s++;
		if (s < es)
			s++;
	}
	else if (token == '\"')
	{
		token = 'a';
		s++;
		while (s < es && *s != '\"')
			s++;
		if (s < es)
			s++;
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
	t_execcmd	*ecmd;
	t_cmd		*cmd;
	t_cmd		*tmp;
	int			tok;
	char		*q;
	char		*eq;
	int			argc;

	argc = 0;
	cmd = execcmd();
	ecmd = (t_execcmd *)cmd;
	cmd = parse_redir(cmd, ps, es);
	while (!peek(ps, es, "|"))
	{
		tok = get_next_token(ps, es, &q, &eq);
		if (tok == '\0')
			break;
		if (tok != 'a')
			panic("Syntax Error");
		ecmd->args[argc] = q;
		ecmd->eargs[argc] = eq;
		argc++;
		if(argc >= MAXARGS - 1)
      		panic("too many args");
		tmp = cmd;
		if (cmd != (t_cmd *)ecmd)
		{
			while (((t_redircmd *)tmp)->subcmd->type == REDIR)
				tmp = ((t_redircmd *)tmp)->subcmd;
			((t_redircmd *)tmp)->subcmd = parse_redir((t_cmd *)ecmd, ps, es);
		}
		else
			cmd = parse_redir(cmd, ps, es);
	}
	ecmd->args[argc] = NULL;
	ecmd->eargs[argc] = NULL;
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
			panic("Syntax Error: Missing file for redirection");
		if (tok == '<')
			cmd = redircmd(parse_redir(subcmd, ps, es), q, eq, O_RDONLY, 0, '<');
		else if (tok == '>')
			cmd = redircmd(parse_redir(subcmd, ps, es), q, eq, O_WRONLY | O_CREAT | O_TRUNC, 1, '>');
		else if (tok == '+')
			cmd = redircmd(parse_redir(subcmd, ps, es), q, eq, O_WRONLY | O_CREAT | O_APPEND, 1, '+');
		else if (tok == '%')
			cmd = redircmd(parse_redir(subcmd, ps, es), q, eq, O_RDONLY, 0, '%');
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
		printf("The redir is : %c\n", rcmd->redirection_type);
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

char *read_input_until_delimiter(const char *delimiter)
{
	char	*line;
	int		buffer_len;
    char	*input_buffer;

	buffer_len = 0;
	input_buffer = (char *)malloc(sizeof(char) * 1024);
	if (!input_buffer)
	{
		panic("malloc");
		exit(1);
	}
	
	int terminal_fd = open("/dev/tty", O_RDONLY);
    dup2(terminal_fd, 0);
    close(terminal_fd);

	int terminal_fd1 = open("/dev/tty", O_WRONLY);

	while (1)
	{
		ft_putstr_fd("> ", terminal_fd1);
		line = get_next_line(0);
		if (ft_strlen(line) == ft_strlen(delimiter) + 1 &&
			ft_strncmp(line, delimiter, ft_strlen(line) - 1) == 0)
			break;
		ft_strlcpy(input_buffer + buffer_len, line, ft_strlen(line) + 1);
		buffer_len += ft_strlen(line);
		free(line);
	}
	free(line);
	close(terminal_fd1);
	return (input_buffer);
}

void	write_input_to_temp_file(char *input)
{
	int	fd;

	fd = open(TEMP_FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		panic("open");
		exit(1);
	}
	if (write(fd, input, ft_strlen(input)) < 0)
	{
		panic("write");
		exit(1);
	}
	close(fd);
}




void	run_cmd(t_cmd *cmd, t_env_var **env_var_list, int exit_status)
{
	int	fd[2];
	t_redircmd	*rcmd;
	t_pipecmd	*pcmd;
	t_execcmd	*ecmd;

	if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		pipe(fd);
		int pid1;
		int pid2;
		if ((pid1 = forking()) == 0)
		{
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
			run_cmd(pcmd->left, env_var_list, exit_status);
		}
		if ((pid2 = forking()) == 0)
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			run_cmd(pcmd->right, env_var_list, exit_status);
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, NULL, 0);
		int status;
		waitpid(pid2, &status, 0);
		int	exit_status;
		
		if (WIFEXITED(status)) {
			exit_status = WEXITSTATUS(status);
		} else {
			exit_status = 1;
		}
		int fd = open("temp", O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd < 0)
		{
			panic("open");
			exit(1);
		}
		if (write(fd, &exit_status, sizeof(int)) < 0)
		{
			panic("write");
			exit(1);
		}
		close(fd);
	}
	else if(cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		if (rcmd->redirection_type != '%')
		{
			close(rcmd->fd);
			if (open(rcmd->file, rcmd->mod, 0644) < 0)
			{
				panic("open");
				exit(1);
			}
		}
		else
		{
			char *input;
			input = read_input_until_delimiter(rcmd->file);
			write_input_to_temp_file(input);
			free(input);
			close(rcmd->fd);
			if (open(TEMP_FILE_NAME, rcmd->mod, 0644) < 0)
			{
				panic("open");
				exit(1);
			}
		}
		run_cmd(rcmd->subcmd, env_var_list, exit_status);
	}
	else if (cmd->type == EXEC)
	{
		
		ecmd = (t_execcmd *)cmd;
		if (ecmd->args[0] == NULL)
			exit(0);
		if (strcmp(ecmd->args[0], "echo") == 0)
			echo(ecmd->args, exit_status);
		else if (ft_strcmp(ecmd->args[0], "env") == 0 && ecmd->args[1] == NULL)
			env(env_var_list);
		else if (ft_strcmp(ecmd->args[0], "export") == 0)
			export(ecmd->args, *env_var_list);
		else if (ft_strcmp(ecmd->args[0], "unset") == 0)
		{
			return;
		}
		else
		{
			
			execvp(ecmd->args[0], ecmd->args);
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(ecmd->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
	}
	exit(0);
}



void	norm_sig(int sig)
{
	if (sig == SIGQUIT)
		ft_printf_fd(STDERR_FILENO, "Quit: %d\n", SIGQUIT);
	else if (sig == SIGINT)
		ft_printf_fd(STDERR_FILENO, "\n");
}


static void	sig(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf_fd(STDERR_FILENO, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("\033[2K\rminishell$ ", 2);
	}
}

int main(int argc, char **argv, char **envp)
{
    char    	*buf;
	t_cmd		*main_tree;
	int			exit_status = 0;
	t_env_var	*env_var_list;
	(void)argc;
	(void)argv;
	env_var_list = NULL;
	copy_env_to_list(envp, &env_var_list);
	
	
	
    while (1)
    {
		signal(SIGINT, sig);
    	signal(SIGQUIT, sig);
        buf = readline("minishell$ ");
		if (buf == NULL)
		{
			ft_printf("exit\n");
			break;
		}
        if (ft_strlen(buf) == 0 || !buf)
            continue;

		main_tree = parse_cmd(buf);


		if (main_tree && main_tree->type == EXEC && ft_strcmp(((t_execcmd *)main_tree)->args[0], "exit") == 0)
		{
			ft_printf("exit\n");
			break;
		}
		else if (main_tree && main_tree->type == EXEC && ft_strcmp(((t_execcmd *)main_tree)->args[0], "export") == 0)
			handle_export_command(((t_execcmd *)main_tree)->args, &env_var_list, &exit_status);
		else if (main_tree && main_tree->type == EXEC && ft_strcmp(((t_execcmd *)main_tree)->args[0], "unset") == 0)
			unset_env_var(((t_execcmd *)main_tree)->args, &env_var_list, &exit_status);
		else if (main_tree && main_tree->type == EXEC && ft_strcmp(((t_execcmd *)main_tree)->args[0], "cd") == 0)
			cd(((t_execcmd *)main_tree)->args, &exit_status);
		else
		{
			signal(SIGINT, norm_sig);
    		signal(SIGQUIT, norm_sig);
			if(forking() == 0)
			{
				// display_tree(main_tree);
				
				run_cmd(main_tree, &env_var_list, exit_status);
			}
			wait(NULL);
			// int status;
			// wait(&status);
			// if (main_tree && (main_tree->type == EXEC || main_tree->type == REDIR))
			// {
			// 	if (WIFEXITED(status))
			// 		exit_status = WEXITSTATUS(status);
			// 	else
			// 		exit_status = 1;
			// 	free(buf);
			// 	unlink(TEMP_FILE_NAME);
			// }
			// else
			// {
			// 	int fd = open("temp", O_RDONLY);
			// 	if (fd < 0)
			// 	{
			// 		panic("open");
			// 		exit(1);
			// 	}
			// 	read(fd, &exit_status, sizeof(int));
			// 	free(buf);
			// 	unlink("temp");
			// 	unlink(TEMP_FILE_NAME);
			// }
		}
    }
    exit(0);
}
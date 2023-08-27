/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:13:57 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/27 09:57:15 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"
#include <sys/wait.h>


void	execute_left_subtree(t_cmd *cmd, int fd[2], t_env_var **env_var_list, int *exit_status)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	run_cmd(cmd, env_var_list, exit_status);
	exit(0);
}

void	execute_right_subtree(t_cmd *cmd, int fd[2], t_env_var **env_var_list, int *exit_status)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	run_cmd(cmd, env_var_list, exit_status);
	exit(0);
}

void write_exit_status_to_file(int exit_status)
{
	int fd;

	fd = open("/tmp/exit_status.tmp", O_WRONLY | O_CREAT | O_APPEND, 0777);
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

void	run_pipe(t_cmd *cmd, t_env_var **env_var_list, int *exit_status)
{
	int			fd[2];
	int			pid1;
	int			pid2;
	int			status;
	t_pipecmd	*pcmd;

	pcmd = (t_pipecmd *)cmd;
	pipe1(fd);
	if ((pid1 = forking()) == 0)
		execute_left_subtree(pcmd->left, fd, env_var_list, exit_status);
	if ((pid2 = forking()) == 0)
		execute_right_subtree(pcmd->right, fd, env_var_list, exit_status);
	close(fd[0]);
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
	{
		*exit_status = WEXITSTATUS(status);
	} else {
		*exit_status = 1;
	}
	write_exit_status_to_file(*exit_status);
}




// void	run_cmd(t_cmd *cmd, t_env_var **env_var_list, int exit_status)
// {
// 	int	fd[2];
// 	t_redircmd	*rcmd;
// 	t_pipecmd	*pcmd;
// 	t_execcmd	*ecmd;

// 	if (cmd->type == PIPE)
// 	{
// 		pcmd = (t_pipecmd *)cmd;
// 		pipe(fd);
// 		int pid1;
// 		int pid2;
// 		if ((pid1 = forking()) == 0)
// 		{
// 			close(fd[0]);
// 			dup2(fd[1], 1);
// 			close(fd[1]);
// 			run_cmd(pcmd->left, env_var_list, exit_status);
// 		}
// 		if ((pid2 = forking()) == 0)
// 		{
// 			close(fd[1]);
// 			dup2(fd[0], 0);
// 			close(fd[0]);
// 			run_cmd(pcmd->right, env_var_list, exit_status);
// 		}
		
// 		signal(SIGINT, SIG_IGN);
// 		signal(SIGQUIT, SIG_IGN);
// 		close(fd[0]);
// 		close(fd[1]);
// 		waitpid(pid1, NULL, 0);
// 		int status;
// 		waitpid(pid2, &status, 0);
// 		int	exit_status;
		
		// if (WIFEXITED(status))
		// {
		// 	exit_status = WEXITSTATUS(status);
		// } else {
		// 	exit_status = 1;
		// }
// 		int fd = open("exit_status.tmp", O_WRONLY | O_CREAT | O_APPEND, 0777);
// 		if (fd < 0)
// 		{
// 			panic("open");
// 			exit(1);
// 		}
// 		if (write(fd, &exit_status, sizeof(int)) < 0)
// 		{
// 			panic("write");
// 			exit(1);
// 		}
// 		close(fd);
// 	}
// 	else if(cmd->type == REDIR)
// 	{
// 		signal(SIGINT, SIG_IGN);
// 		signal(SIGQUIT, SIG_IGN);
// 		rcmd = (t_redircmd *)cmd;
// 		if (rcmd->redirection_type != '%')
// 		{
// 			close(rcmd->fd);
// 			if (open(rcmd->file, rcmd->mod, 0644) < 0)
// 			{
// 				panic("open");
// 				exit(1);
// 			}
// 		}
// 		else
// 		{
// 			char *input;
// 			input = read_input_until_delimiter(rcmd->file);
// 			write_input_to_temp_file(input);
// 			free(input);
// 			close(rcmd->fd);
// 			if (open(TEMP_FILE_NAME, rcmd->mod, 0644) < 0)
// 			{
// 				panic("open");
// 				exit(1);
// 			}
// 		}
// 		run_cmd(rcmd->subcmd, env_var_list, exit_status);
// 	}
// 	else if (cmd->type == EXEC)
// 	{
// 		ecmd = (t_execcmd *)cmd;
// 		if (ecmd->args[0] == NULL)
// 		{
// 			exit(0);
// 		}
// 		else if (strcmp(ecmd->args[0], "echo") == 0)
// 		{
// 			echo(ecmd->args, *env_var_list, exit_status);
// 		}
// 		else if (ft_strcmp(ecmd->args[0], "env") == 0 && ecmd->args[1] == NULL)
// 			env(env_var_list);
// 		else if (ft_strcmp(ecmd->args[0], "export") == 0)
// 			export(ecmd->args, *env_var_list);
// 		else if (ft_strcmp(ecmd->args[0], "unset") == 0)
// 		{
// 			exit(0);
// 		}
// 		else if (ft_strcmp(ecmd->args[0], "pwd") == 0)
// 		{
// 			char *pwd = getcwd(NULL, 0);
// 			ft_printf("%s\n", pwd);
// 			free(pwd);
// 		}
// 		else
// 		{
			
// 			execvp(ecmd->args[0], ecmd->args);
// 			ft_putstr_fd("minishell: ", 2);
// 			ft_putstr_fd(ecmd->args[0], 2);
// 			ft_putstr_fd(": command not found\n", 2);          
// 			exit(127);
// 		}
// 	}
// 	exit(0);
// }
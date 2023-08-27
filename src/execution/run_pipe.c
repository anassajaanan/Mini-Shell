/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:13:57 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/27 10:41:37 by aajaanan         ###   ########.fr       */
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
		panic("open");
	if (write(fd, &exit_status, sizeof(int)) < 0)
		panic("write");
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

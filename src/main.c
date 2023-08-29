/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:53:51 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/29 15:45:19 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_built_in_command(t_cmd *tree)
{
	t_execcmd	*ecmd;

	if (tree && tree->type == EXEC)
	{
		ecmd = (t_execcmd *)tree;
		if (ft_strcmp(ecmd->argv[0], "export") == 0)
			return (1);
		else if (ft_strcmp(ecmd->argv[0], "unset") == 0)
			return (1);
		else if (ft_strcmp(ecmd->argv[0], "cd") == 0)
			return (1);
	}
	return (0);
}

void	execute_built_in_command(t_execcmd *ecmd, t_env_var **env_var_list, int *exit_status)
{
	if (ft_strcmp(ecmd->argv[0], "export") == 0)
		export_command(ecmd->argv, env_var_list, exit_status);
	else if (ft_strcmp(ecmd->argv[0], "unset") == 0)
		unset_env_var(ecmd->argv, env_var_list, exit_status);
	else if (ft_strcmp(ecmd->argv[0], "cd") == 0)
		cd(ecmd->argv, exit_status, *env_var_list);
}

void	save_child_pid(int pid)
{
	int	fd;

	fd = open("/tmp/child_pid.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		panic("open");
	if (write(fd, &pid, sizeof(int)) < 0)
		panic("write");
	close(fd);
}

void	get_exit_status(t_cmd *tree, int *exit_status, int status)
{
	int	fd;
	
	if (tree && (tree->type == EXEC || tree->type == REDIR))
	{
		if (WIFEXITED(status))
			*exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			*exit_status = WTERMSIG(status) + 128;
		else
			*exit_status = 1;
	}
	else
	{
		fd = open("/tmp/exit_status.tmp", O_RDONLY);
		if (fd < 0)
			panic("open");
		if (read(fd, exit_status, sizeof(int)) < 0)
			panic("read");
		close(fd);
	}
}

void	cleanup_files(void)
{
	unlink("/tmp/exit_status.tmp");
	unlink("/tmp/child_pid.tmp");
}

void	cleanup(t_params *params)
{
	cleanup_files();
	free1(params->buf);
	free_tree(params->tree);
}

void	process_quoted_args(t_cmd *cmd)
{
	t_execcmd	*ecmd;
	t_redircmd	*rcmd;
	t_pipecmd	*pcmd;

	if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		process_quoted_args(pcmd->left);
		process_quoted_args(pcmd->right);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		process_quoted_args(rcmd->subcmd);
	}
	else if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		if (ecmd->argv[0] && (ft_strcmp(ecmd->argv[0], "grep") == 0 || ft_strcmp(ecmd->argv[0], "cat") == 0))
		{
			for (int i = 1; ecmd->argv[i]; i++)
			{
				if (ecmd->argv[i][0] == '\"' && ecmd->argv[i][ft_strlen(ecmd->argv[i]) - 1] == '\"')
				{
					ecmd->argv[i] = ecmd->argv[i] + 1;
					ecmd->eargv[i] = ecmd->eargv[i] - 1;
					ecmd->eargv[i][0] = '\0';
				}
			}
		}
	}
}

void	execute_command(t_params *params, int *exit_status)
{
	set_signal_handler(params->tree);
	if (forking() == 0)
	{
		save_child_pid(getpid());
		process_quoted_args(params->tree);
		run_cmd(params->tree, params, exit_status);
	}
	int status;
	waitpid(-1, &status, 0);
	get_exit_status(params->tree, exit_status, status);
	if (params->tree->type == EXEC && ft_strcmp(((t_execcmd *)params->tree)->argv[0], "exit") == 0)
	{
		cleanup_files();
		free_exit(params, *exit_status);
	}
	cleanup(params);
}


int	is_whitespace_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_whitespace(str[i]))
			return (0);
		i++;
	}
	return (1);
}


int main(int argc, char **argv, char **envp)
{
	t_params	params;
	int			exit_status;

	(void)argc;
	(void)argv;
	params.env_var_list = NULL;
	init_env_var_list(envp, &params.env_var_list);
	while (1)
	{
		setup_signals();
		params.buf = readline(BCYN "minishell$ " reset);
		if (!params.buf)
		{
			ft_printf_fd(STDOUT_FILENO, "exit\n");
			break;
		}
		if (ft_strlen(params.buf) == 0 || is_whitespace_string(params.buf))
		{
			free1(params.buf);
			continue ;
		}
		if (!validate_command(params.buf, &exit_status))
		{
			free1(params.buf);
			continue ;
		}
		params.tree = parse_cmd(params.buf, &exit_status);
		if (is_built_in_command(params.tree))
		{
			execute_built_in_command((t_execcmd *)params.tree, &params.env_var_list, &exit_status);
			free1(params.buf);
			free_tree(params.tree);
		}
		else
			execute_command(&params, &exit_status);
	}
	free_env_var_list(params.env_var_list);
	return (exit_status);
}


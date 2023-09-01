/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:30:45 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/01 15:36:03 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"

void	handle_variable_substitution(t_execcmd *ecmd, t_env_var **env_var_list)
{
	int	i;
	
	(void)env_var_list;
	while (ecmd->argv[0] && ecmd->argv[0][0] == '\0')
	{
		i = 0;
		while (ecmd->argv[i] && ecmd->argv[i + 1])
		{
			ecmd->argv[i] = ecmd->argv[i + 1];
			i++;
		}
		ecmd->argv[i] = NULL;
	}
}

void handle_executable_path(t_execcmd *ecmd, t_params *params)
{
	if (ecmd->argv[0] == NULL)
		free_exit(params, 0);
	else if (ft_strchr("./", ecmd->argv[0][0]))
	{
		struct stat	path_stat;
		if (stat(ecmd->argv[0], &path_stat) == 0)
		{
			if (S_ISDIR(path_stat.st_mode))
			{
				ft_printf_fd(STDERR_FILENO, "minishell: %s: is a directory\n", ecmd->argv[0]);
				free_exit(params, 126);
			}
			else if (access(ecmd->argv[0], X_OK) != 0)
			{
				ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied\n", ecmd->argv[0]);
				free_exit(params, 126);
			}
		}
		else
		{
			ft_printf_fd(STDERR_FILENO, "minishell: %s: No such file or directory\n", ecmd->argv[0]);
			free_exit(params, 127);
		}
	}
}

int	is_builtin_command(t_execcmd *ecmd)
{
	if (ft_strcmp(ecmd->argv[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(ecmd->argv[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(ecmd->argv[0], "env") == 0 && ecmd->argv[1] == NULL)
		return (1);
	else if (ft_strcmp(ecmd->argv[0], "export") == 0)
		return (1);
	else if (ft_strcmp(ecmd->argv[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(ecmd->argv[0], "pwd") == 0)
		return (1);
	else
		return (0);
		
}

void	execute_builtin_commands(t_execcmd *ecmd, t_params *params, int exit_status)
{
	if (ft_strcmp(ecmd->argv[0], "echo") == 0)
		echo(ecmd->argv);
	else if (ft_strcmp(ecmd->argv[0], "exit") == 0)
		exit_command(ecmd->argv, params);
	else if (ft_strcmp(ecmd->argv[0], "env") == 0 && ecmd->argv[1] == NULL)
		env(&params->env_var_list);
	else if (ft_strcmp(ecmd->argv[0], "export") == 0)
		export(ecmd->argv, params->env_var_list);
	else if (ft_strcmp(ecmd->argv[0], "unset") == 0)
		free_exit(params, 0);
	else if (ft_strcmp(ecmd->argv[0], "pwd") == 0)
		pwd(&exit_status);
}

char	*find_command_path(char *cmd, char *path_var)
{
	int		i;
	char	**paths;
	char	*command;
	char	*binary_path;

	paths = ft_split(path_var, ':');
	command = ft_strjoin("/", cmd);
	i = 0;
	while (paths[i])
	{
		binary_path = ft_strjoin(paths[i], command);
		if (access(binary_path, X_OK) == 0)
		{
			free1(command);
			free_split(paths);
			return (binary_path);
		}
		free1(binary_path);
		i++;
	}
	free1(command);
	free_split(paths);
	return (NULL);
}

void	run_exec(t_cmd *cmd, t_params *params, int *exit_status)
{
	t_execcmd	*ecmd;
	char		*path_var;
	char		*binary_path;

	binary_path = NULL;
	ecmd = (t_execcmd *)cmd;
	handle_variable_substitution(ecmd, &params->env_var_list);
	handle_executable_path(ecmd, params);
	if (is_builtin_command(ecmd))
	{
		execute_builtin_commands(ecmd, params, *exit_status);
		free_exit(params, 0);
	}
	else
	{
		if (access(ecmd->argv[0], X_OK) == 0)
		{
			execve(ecmd->argv[0], ecmd->argv, NULL);
			ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n", ecmd->argv[0]);
			free_exit(params, 127);
		}
		path_var = getenv_value("PATH", params->env_var_list);
		if (path_var == NULL)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: %s: No such file or directory\n", ecmd->argv[0]);
			free_exit(params, 127);
		}
		binary_path = find_command_path(ecmd->argv[0], path_var);
		if (binary_path == NULL)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n", ecmd->argv[0]);
			free_exit(params, 127);
		}
		execve(binary_path, ecmd->argv, NULL);
		free1(binary_path);
		free_exit(params, 126);
	}
}
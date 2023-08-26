/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:30:45 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/26 17:53:38 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"
#include <sys/stat.h>

void	handle_variable_substitution(t_execcmd *ecmd, t_env_var **env_var_list)
{
	int		i;
	char	*value;
	
	while (ecmd->argv[0] && ecmd->argv[0][0] == '$' && !ft_strchr("?\0", ecmd->argv[0][1]))
	{
		value = getenv_value(ecmd->argv[0] + 1, env_var_list);
		if (value)
		{
			ecmd->argv[0] = value;
			break;
		}
		else
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
}

void handle_executable_path(t_execcmd *ecmd)
{
	if (ecmd->argv[0] == NULL)
		exit(0);
	else if (ft_strchr("./", ecmd->argv[0][0]))
	{
		struct stat	path_stat;
		if (stat(ecmd->argv[0], &path_stat) == 0)
		{
			if (S_ISDIR(path_stat.st_mode))
			{
				ft_printf_fd(STDERR_FILENO, "minishell: %s: is a directory\n", ecmd->argv[0]);
				exit(126);
			}
			else if (access(ecmd->argv[0], X_OK) != 0)
			{
				ft_printf_fd(STDERR_FILENO, "minishell: %s: Permission denied\n", ecmd->argv[0]);
				exit(126);
			}
		}
		else
		{
			ft_printf_fd(STDERR_FILENO, "minishell: %s: No such file or directory\n", ecmd->argv[0]);
			exit(127);
		}
	}
}

int	is_builtin_command(t_execcmd *ecmd)
{
	if (ft_strcmp(ecmd->argv[0], "echo") == 0)
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

void	execute_builtin_commands(t_execcmd *ecmd, t_env_var **env_var_list, int exit_status)
{
	if (ft_strcmp(ecmd->argv[0], "echo") == 0)
		echo(ecmd->argv, *env_var_list, exit_status);
	else if (ft_strcmp(ecmd->argv[0], "env") == 0 && ecmd->argv[1] == NULL)
		env(env_var_list);
	else if (ft_strcmp(ecmd->argv[0], "export") == 0)
		export_cmd(ecmd->argv, env_var_list);
	else if (ft_strcmp(ecmd->argv[0], "unset") == 0)
		exit(0);
	else if (ft_strcmp(ecmd->argv[0], "pwd") == 0)
		;//pwd
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
			free(command);
			free_split(paths);
			return (binary_path);
		}
		free(binary_path);
		i++;
	}
	free(command);
	free_split(paths);
	return (NULL);
}

void	run_exec(t_cmd *cmd, t_env_var **env_var_list, int exit_status)
{
	t_execcmd	*ecmd;
	char		*path_var;
	char		*binary_path;

	ecmd = (t_execcmd *)cmd;
	handle_variable_substitution(ecmd, env_var_list);
	handle_executable_path(ecmd);
	if (is_builtin_command(ecmd))
	{
		exit(0);
	}
	else
	{
		path_var = getenv_value("PATH", env_var_list);
		if (path_var == NULL)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: %s: No such file or directory\n", ecmd->argv[0]);
			exit(127);
		}
		binary_path = find_command_path(ecmd->argv[0], path_var);
		if (binary_path == NULL)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n", ecmd->argv[0]);
			exit(127);
		}
		execve(binary_path, ecmd->argv, NULL);
		free(binary_path);
		exit(126);
	}
	free(binary_path);
	exit(0);
}
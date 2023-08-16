/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:02:21 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/16 07:54:26 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	change_to_home_directory(int *exit_status)
{
	char	*home_dir;
	
	home_dir = getenv("HOME");
	if (home_dir)
	{
		if (chdir(home_dir) != 0)
		{
			perror("cd");
			*exit_status = 1;
		}
	}
	else
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("cd");
			*exit_status = 1;
		}
	}
}

void	change_to_directory(char *directory, int *exit_status)
{
	if (chdir(directory) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(directory, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		*exit_status = 1;
	}
}

void	expand_tilde(char	*path, int *exit_status)
{
	char	*new_path;
	
	if (ft_strcmp(path, "~") == 0)
		change_to_home_directory(exit_status);
	else if (path[0] == '~')
	{
		new_path = ft_strjoin(getenv("HOME"), path + 1);
		if (chdir(new_path) != 0)
		{
			if (ft_strcmp(getenv("USER"), path + 1) == 0)
				change_to_home_directory(exit_status);
			else
			{
				ft_putstr_fd("minishell: cd: ", 2);
				ft_putstr_fd(path + 1, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				*exit_status = 1;
			}
		}
		free(new_path);
	}
}

void	expand_environment_variables(char *path, int *exit_status)
{
	char	*env_var;

	env_var = getenv(path + 1);
	if (env_var)
		change_to_directory(env_var, exit_status);
	else
		change_to_home_directory(exit_status);
}

void	cd(char **args, int *exit_status)
{
	if (args[1] == NULL)
		change_to_home_directory(exit_status);
	else
	{
		if (ft_strcmp(args[1], "~") == 0)
			change_to_home_directory(exit_status);
		else if (args[1][0] == '~')
			expand_tilde(args[1], exit_status);
		else if (args[1][0] == '$')
			expand_environment_variables(args[1], exit_status);
		else
			change_to_directory(args[1], exit_status);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:02:21 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/15 15:18:47 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	change_to_home_directory()
{
	char	*home_dir;
	
	home_dir = getenv("HOME");
	if (home_dir)
	{
		if (chdir(home_dir) != 0)
			perror("cd");
	}
	else
	{
		if (chdir(getenv("HOME")) != 0)
			perror("cd");
	}
}

void	change_to_directory(char *directory)
{
	if (chdir(directory) != 0)
		perror("cd");
}

void	expand_tilde(char	*path)
{
	char	*new_path;
	
	if (ft_strcmp(path, "~") == 0)
		change_to_home_directory();
	else if (path[0] == '~')
	{
		new_path = ft_strjoin(getenv("HOME"), path + 1);
		if (chdir(new_path) != 0)
		{
			if (ft_strcmp(getenv("USER"), path + 1) == 0)
				change_to_home_directory();
			else
				perror("cd");
		}
		free(new_path);
	}
}

void	expand_environment_variables(char *path)
{
	char	*env_var;

	env_var = getenv(path + 1);
	if (env_var)
		change_to_directory(env_var);
	else
		change_to_home_directory();
}



void	cd(char **args)
{
	if (args[1] == NULL)
		change_to_home_directory();
	else
	{
		if (ft_strcmp(args[1], "~") == 0)
			change_to_home_directory();
		else if (args[1][0] == '~')
			expand_tilde(args[1]);
		else if (args[1][0] == '$')
			expand_environment_variables(args[1]);
		else
			change_to_directory(args[1]);
	}
}
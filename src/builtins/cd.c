/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:02:21 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/02 15:51:01 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtins.h"

void	update_pwd(t_env_var *env_var_list)
{
	char		*pwd;
	t_env_var	*tmp;
	t_env_var	*old_pwd_node;
	
	pwd = getcwd(NULL, 0);
	tmp = env_var_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			old_pwd_node = env_var_new(ft_strdup("OLDPWD"), tmp->value);
			env_var_insert_sorted(&env_var_list, old_pwd_node);
			tmp->value = ft_strdup(pwd);
			free(pwd);
			return ;
		}
		tmp = tmp->next;
	}
}

void	change_to_home_directory(int *exit_status, t_env_var *env_var_list)
{
	char	*home_dir;

	home_dir = getenv_value("HOME", env_var_list);
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
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		*exit_status = 1;
	}
}

void	cd(char **argv, int *exit_status, t_env_var *env_var_list)
{
	if (argv[1] == NULL)
	{
		change_to_home_directory(exit_status, env_var_list);
		update_pwd(env_var_list);
		return ;
	}
	if (ft_strcmp(argv[1], "-") == 0)
	{
		if (chdir(getenv_value("OLDPWD", env_var_list)) != 0)
		{
			ft_printf_fd(2, "minishell: cd: OLDPWD not set\n");
			*exit_status = 1;
		}
		else
		{
			ft_printf("%s\n", getenv_value("OLDPWD", env_var_list));
			update_pwd(env_var_list);
		}
		return ;
	}
	if (argv[1][0] == '~')
	{
		char *path = ft_strjoin(getenv_value("HOME", env_var_list), argv[1] + 1);
		if (chdir(path) != 0)
		{
			ft_printf_fd(2, "minishell: cd: %s: No such file or directory\n", path);
			*exit_status = 1;
		}
		else
			update_pwd(env_var_list);
		free(path);
		return ;
	}
	if (chdir(argv[1]) != 0)
	{
		ft_printf_fd
			(2, "minishell: cd: %s: No such file or directory\n", argv[1]);
		*exit_status = 1;
	}
	else
		update_pwd(env_var_list);
}

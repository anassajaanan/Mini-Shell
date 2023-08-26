/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:02:21 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/26 17:34:53 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


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

static char	*get_variable_name(char *arg)
{
	int i;

	i = 0;
	while (arg[i] && ((ft_isalnum(arg[i]) || arg[i] == '_')))
		i++;
	return (ft_substr(arg, 0, i));
}


void	update_pwd(t_env_var *env_var_list)
{
	char		*pwd;
	t_env_var	*tmp;
	t_env_var	*old_pwd;
	
	pwd = getcwd(NULL, 0);
	tmp = env_var_list;
	
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			old_pwd = env_var_new(ft_strdup("OLDPWD"), tmp->value);
			env_var_insert_sorted(&env_var_list, old_pwd);
			tmp->value = ft_strdup(pwd);
			free(pwd);
			return ;
		}
		tmp = tmp->next;
	}
}

void	cd(char **argv, int *exit_status, t_env_var *env_var_list)
{
	int				i;
	t_queue_char	q;
	char			*path;

	path = argv[1];
	init_queue_char(&q);
	if (path == NULL)
	{
		change_to_home_directory(exit_status, env_var_list);
		update_pwd(env_var_list);
		return;
	}
	else
	{
		i = 0;
		while (path[i])
		{
			if (path[i] == '\'')
			{
				i++;
				while (path[i] && path[i] != '\'')
				{
					enqueue_char(&q, path[i]);
					i++;
				}
				if (path[i] == '\'')
					i++;
			}
			else if (path[i] == '\"')
			{
				i++;
				while (path[i] && path[i] != '\"')
				{
					if (path[i] == '$' && path[i + 1] == '?')
					{
						char *exit_status_str = ft_itoa(*exit_status);
						enqueue_str(&q, exit_status_str);
						free(exit_status_str);
						i += 2;
					}
					else if (path[i] == '$')
					{
						i++;
						char *var_name = get_variable_name(path + i);
						char *var_value = getenv_value(var_name, env_var_list);
						if (var_value)
							enqueue_str(&q, var_value);
						i += ft_strlen(var_name);
						free(var_name);
					}
					else
					{
						enqueue_char(&q, path[i]);
						i++;
					}
				}
				if (path[i] == '\"')
					i++;
			}
			else if (path[i] == '$')
			{
				i++;
				if (path[i] == '?')
				{
					char *exit_status_str = ft_itoa(*exit_status);
					enqueue_str(&q, exit_status_str);
					free(exit_status_str);
					i++;
				}
				else
				{
					char *var_name = get_variable_name(path + i);
					char *var_value = getenv_value(var_name, env_var_list);
					if (var_value)
						enqueue_str(&q, var_value);
					i += ft_strlen(var_name);
					free(var_name);
				}
			}
			else if (path[i] == '~')
			{
				char	*home_dir = getenv_value("HOME", env_var_list);
				if (home_dir)
				{
					enqueue_str(&q, home_dir);
					i++;
				}
				else
				{
					enqueue_char(&q, path[i]);
					i++;
				}
			}
			else
			{
				enqueue_char(&q, path[i]);
				i++;
			}
			
		}
	}
	char	*new_path = queue_to_str(&q);
	if (chdir(new_path) != 0)
	{
		ft_printf_fd(2, "minishell: cd: %s: No such file or directory\n", new_path);
		*exit_status = 1;
	}
	else
		update_pwd(env_var_list);
	free(new_path);
}
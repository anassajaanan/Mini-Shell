/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 09:11:13 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/01 19:50:47 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtins.h"

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

char	*get_cd_variable_name(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && ((ft_isalnum(arg[i]) || arg[i] == '_')))
		i++;
	return (ft_substr(arg, 0, i));
}

void	update_pwd(t_env_var *env_var_list)
{
	char		*pwd;
	t_env_var	*tmp;

	pwd = getcwd(NULL, 0);
	tmp = env_var_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(pwd);
			free(pwd);
			return ;
		}
		tmp = tmp->next;
	}
}

char	**get_new_path_2(char *path, int *exit_status, char *home_dir, int i)
{
	char	**values;

	values = malloc(sizeof(char *) * 3);
	values[2] = NULL;
	if (path[i] == '\"')
	{
		values[0] = path;
		values[1] = (char *)exit_status;
	}
	else if (path[i] == '$')
	{
		values[0] = path;
		values[1] = (char *)exit_status;
	}
	else if (path[i] == '~')
	{
		values[0] = path;
		values[1] = home_dir;
	}
	return (values);
}

void	get_new_path(char *path, int *exit_status,
	t_env_var *env_var_list, t_queue_char *q)
{
	int		i;
	char	*home_dir;
	char	**values;

	i = 0;
	home_dir = NULL;
	values = NULL;
	while (path[i])
	{
		values = get_new_path_2(path, exit_status, home_dir, i);
		if (path[i] == '\'')
			handle_single_quote_cd(&i, path, q);
		else if (path[i] == '\"')
			handle_double_quotes_cd(values, env_var_list, q, &i);
		else if (path[i] == '$')
			handle_dollar_sign_cd(values, env_var_list, &i, q);
		else if (path[i] == '~')
			tilde(values, q, env_var_list, &i);
		else
			enqueue_char(q, path[i++]);
		if (values)
			free(values);
	}
}

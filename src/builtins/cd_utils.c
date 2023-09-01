/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 09:10:10 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/01 19:50:55 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtins.h"

void	handle_single_quote_cd(int *i, char *path, t_queue_char *q)
{
	(*i)++;
	while (path[*i] && path[*i] != '\'')
		enqueue_char(q, path[(*i)++]);
	if (path[*i] == '\'')
		(*i)++;
}

void	tilde(char **path_and_home_dir,
	t_queue_char *q, t_env_var *env_var_list, int *i)
{
	path_and_home_dir[1] = getenv_value("HOME", env_var_list);
	if (path_and_home_dir[1])
		enqueue_str(q, path_and_home_dir[1]);
	else
		enqueue_char(q, path_and_home_dir[1][*i]);
	(*i)++;
}

void	handle_dollar_sign_cd(char **vars,
	t_env_var *env_var_list, int *i, t_queue_char *q)
{
	char	*var_name;
	char	*var_value;
	char	*path;
	char	*exit_status_str;
	int		*exit_status;

	path = vars[0];
	exit_status = (int *)vars[1];
	if (path[++(*i)] == '?')
	{
		exit_status_str = ft_itoa(*exit_status);
		enqueue_str(q, exit_status_str);
		free(exit_status_str);
		i++;
	}
	else
	{
		var_name = get_cd_variable_name(path + *i);
		var_value = getenv_value(var_name, env_var_list);
		if (var_value)
			enqueue_str(q, var_value);
		(*i) += ft_strlen(var_name);
		free(var_name);
	}
}

void	handle_double_quotes_2_cd(char *path,
	t_env_var *env_var_list, t_queue_char *q, int *i)
{
	char	*var_name;
	char	*var_value;

	if (path[*i] == '$')
	{
		(*i)++;
		var_name = get_cd_variable_name(path + *i);
		var_value = getenv_value(var_name, env_var_list);
		if (var_value)
			enqueue_str(q, var_value);
		(*i) += ft_strlen(var_name);
		free(var_name);
	}
	else
		enqueue_char(q, path[(*i)++]);
}

void	handle_double_quotes_cd(char **vars,
	t_env_var *env_var_list, t_queue_char *q, int *i)
{
	char	*exit_status_str;
	char	*path;
	int		*exit_status;

	path = vars[0];
	exit_status = (int *)vars[1];
	(*i)++;
	while (path[*i] && path[*i] != '\"')
	{
		if (path[*i] == '$' && path[(*i) + 1] == '?')
		{
			exit_status_str = ft_itoa(*exit_status);
			enqueue_str(q, exit_status_str);
			free(exit_status_str);
			(*i) += 2;
		}
		else
			handle_double_quotes_2_cd(path, env_var_list, q, i);
	}
	if (path[*i] == '\"')
		(*i)++;
}

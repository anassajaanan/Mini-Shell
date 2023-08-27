/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 07:09:20 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/27 14:50:33 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtins.h"

void	print_environment_variables(t_env_var *env_var_list)
{
	t_env_var	*current;

	current = env_var_list;
	while (current)
	{
		if (current->value)
			ft_printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			ft_printf("declare -x %s\n", current->key);
		current = current->next;
	}
}

void	export(char **args, t_env_var *env_var_list)
{
	if (!args[1])
	{
		print_environment_variables(env_var_list);
		return ;
	}
}

char	*extract_variable_name(char *arg, char *equal_sign)
{
	char	*key;

	if (!equal_sign)
		return (ft_strdup(arg));
	key = ft_substr(arg, 0, equal_sign - arg);
	return (key);
}

static int	is_valid_variable_name(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	handle_export_command_2(char *equal_sign,
	char *key, t_env_var **env_var_list)
{
	t_env_var	*new_node;

	if (!equal_sign)
	{
		new_node = env_var_new(key, NULL);
		env_var_insert_sorted(env_var_list, new_node);
	}
	else
	{
		new_node = env_var_new(key, ft_strdup(equal_sign + 1));
		env_var_insert_sorted(env_var_list, new_node);
	}
}

void	handle_export_command(char **args,
	t_env_var **env_var_list, int *exit_status)
{
	int			i;
	char		*key;
	char		*equal_sign;

	if (!args[1])
	{
		print_environment_variables(*env_var_list);
		return ;
	}
	i = 0;
	while (args[++i])
	{
		equal_sign = ft_strchr(args[i], '=');
		key = extract_variable_name(args[i], equal_sign);
		if (!is_valid_variable_name(key))
		{
			ft_printf_fd(STDERR_FILENO,
				"minishell: export: `%s': not a valid identifier\n", args[i]);
			*exit_status = 1;
			i++;
			free(key);
			continue ;
		}
	}
}

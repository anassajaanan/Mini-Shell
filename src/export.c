/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 07:09:20 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/16 08:26:32 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	handle_export_command(char **args, t_env_var **env_var_list, int *exit_status)
{
	int			i;
	char		**key_value;
	char		*equal_sign;
	t_env_var	*new_node;
	
	if (!args[1])
	{
		print_environment_variables(*env_var_list);
		return ;
	}
	i = 1;
	while (args[i])
	{
		if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			*exit_status = 1;
			i++;
			continue ;
		}
		equal_sign = ft_strchr(args[i], '=');
		if (!equal_sign)
		{
			new_node = env_var_new(ft_strdup(args[i]), NULL);
			env_var_insert_sorted(env_var_list, new_node);
		}
		else
		{
			key_value = ft_split(args[i], '=');
			new_node = env_var_new(ft_strdup(key_value[0]), ft_strdup(equal_sign + 1));
			env_var_insert_sorted(env_var_list, new_node);
			free_args(key_value);
		}
		i++;
	}
}
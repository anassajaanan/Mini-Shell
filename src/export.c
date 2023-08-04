/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:12:36 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/04 14:57:27 by aajaanan         ###   ########.fr       */
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

void	handle_export_command(t_params *params)
{
	int			i;
	char		**key_value;
	char		*equal_sign;
	t_env_var	*new_node;
	
	if (params->args[1] == NULL)
		print_environment_variables(params->env_var_list);
	else
	{
		i = 1;
		while (params->args[i])
		{
			if (ft_isdigit(params->args[i][0]))
			{
				ft_printf("minishell: export: `%s': not a valid identifier\n", params->args[i]);
				i++;
				continue ;
			}
			equal_sign = ft_strchr(params->args[i], '=');
			if (!equal_sign)
			{
				new_node = env_var_new(ft_strdup(params->args[i]), NULL);
				env_var_insert_sorted(&params->env_var_list, new_node);
			}
			else
			{
				key_value = ft_split(params->args[i], '=');
				new_node = env_var_new(ft_strdup(key_value[0]), ft_strdup(equal_sign + 1));
				env_var_insert_sorted(&params->env_var_list, new_node);
				free_args(key_value);
			}
			i++;
		}
	}
}
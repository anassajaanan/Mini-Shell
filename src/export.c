/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:12:36 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/04 10:35:18 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_environment_variables(t_env_var *env_var_list)
{
	t_env_var	*current;

	current = env_var_list;
	while (current)
	{
		ft_printf("%s=\"%s\"\n", current->key, current->value);
		current = current->next;
	}
}

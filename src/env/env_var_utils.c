/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:23:23 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/24 12:23:52 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/env.h"

void	free_env_var_node(t_env_var *node)
{
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

void	free_env_var_list(t_env_var *env_var_list)
{
	t_env_var	*tmp;
	t_env_var	*current;

	current = env_var_list;
	while (current)
	{
		tmp = current->next;
		free_env_var_node(current);
		current = tmp;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:27:02 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/14 17:31:45 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	unset_env_var(char **args, t_env_var **env_var_list)
{
	int			i;
	t_env_var	*p;
	t_env_var	*q;
	
	i = 1;
	while (args[i])
	{
		p = *env_var_list;
		q = NULL;
		if (strcmp((*env_var_list)->key, args[i]) == 0)
		{
			*env_var_list = (*env_var_list)->next;
			free_env_var_node(p);
			return;
		}
		while (p && strcmp(p->key, args[i]) != 0)
		{
			q = p;
			p = p->next;
		}
		if (p == NULL)
			return ;
		q->next = p->next;
		free_env_var_node(p);
		i++;
	}
}

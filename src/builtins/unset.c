/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:27:02 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/27 15:53:12 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtins.h"

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

void	remove_env_var(t_env_var **env_var_list, char *arg)
{
	t_env_var	*p;
	t_env_var	*q;

	p = *env_var_list;
	q = NULL;
	while (p && ft_strcmp(p->key, arg) != 0)
	{
		q = p;
		p = p->next;
	}
	if (p == NULL)
		return ;
	q->next = p->next;
	free_env_var_node(p);
}

void	unset_env_var(char **args, t_env_var **env_var_list, int *exit_status)
{
	int			i;
	t_env_var	*p;
	
	i = 1;
	while (args[i])
	{
		if (!is_valid_variable_name(args[i]))
		{
			ft_printf_fd(2, "minishell: unset: `%s': not a valid identifier\n", args[i]);
			*exit_status = 1;
			i++;
			continue ;
		}
		p = *env_var_list;
		if (ft_strcmp((*env_var_list)->key, args[i]) == 0)
		{
			*env_var_list = (*env_var_list)->next;
			free_env_var_node(p);
			return;
		}
		remove_env_var(env_var_list, args[i]);
		i++;
	}
}

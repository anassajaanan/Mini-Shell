/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:04:49 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/04 13:38:11 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env_var	*env_var_new(char *key, char *value)
{
	t_env_var	*env_var_node;

	env_var_node = (t_env_var *)malloc(sizeof(t_env_var));
	if (!env_var_node)
		return (NULL);
	env_var_node->key = key;
	env_var_node->value = value;
	env_var_node->next = NULL;
	return (env_var_node);
}

void	env_var_add_back(t_env_var **env_var_list, t_env_var *new_node)
{
	t_env_var	*last;

	if (!env_var_list)
		return ;
	if (!*env_var_list)
	{
		*env_var_list = new_node;
		return ;
	}
	last = *env_var_list;
	while (last->next)
		last = last->next;
	last->next = new_node;
}

void	env_var_insert_sorted(t_env_var **env_var_list, t_env_var *new_node)
{
	t_env_var	*p;
	t_env_var	*q;

	p = *env_var_list;
	q = NULL;
	if (!env_var_list || !new_node)
		return ;
	if (!(*env_var_list))
	{
		*env_var_list = new_node;
		return ;
	}
	if (strcmp(new_node->key, (*env_var_list)->key) < 0)
	{
		new_node->next = *env_var_list;
		*env_var_list = new_node;
		return;
	}
	while (p && strcmp(p->key, new_node->key) < 0)
	{
		q = p;
		p = p->next;
	}
	q->next = new_node;
	new_node->next = p;
}

void	copy_env_to_list(t_env_var **env_var_list)
{
	char		**env;
	extern char	**environ;
	char		*value;
	char		**key_value;
	t_env_var	*new_node;
	
	env = environ;
	int i = 0;
	while (env[i])
	{
		key_value = ft_split(env[i], '=');
		value = ft_strchr(env[i], '=') + 1;
		new_node = env_var_new(ft_strdup(key_value[0]), ft_strdup(value));
		env_var_insert_sorted(env_var_list, new_node);
		free_args(key_value);
		i++;
	}
}

void	free_env_var_list(t_env_var *env_var_list)
{
	t_env_var	*current;
	t_env_var	*tmp;

	current = env_var_list;
	while (current)
	{
		tmp	= current;
		current = current->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
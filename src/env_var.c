/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:04:49 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/04 18:58:25 by aajaanan         ###   ########.fr       */
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

int	env_var_update_value(t_env_var **env_var_list, t_env_var *new_node)
{
	t_env_var	*tmp;

	tmp = *env_var_list;
	while (tmp)
	{
		if (strcmp(tmp->key, new_node->key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_node->value);
			free_env_var_node(new_node);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	env_var_insert_sorted(t_env_var **env_var_list, t_env_var *new_node)
{
	t_env_var	*p;
	t_env_var	*q;

	p = *env_var_list;
	q = NULL;
	if (!env_var_list || !new_node)
		return ;
	if (env_var_update_value(env_var_list, new_node))
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

void	unset_env_var(t_params *params)
{
	int			i;
	t_env_var	*p;
	t_env_var	*q;
	
	i = 1;
	while (params->args[i])
	{
		p = params->env_var_list;
		q = NULL;
		if (strcmp(params->env_var_list->key, params->args[i]) == 0)
		{
			params->env_var_list = params->env_var_list->next;
			free_env_var_node(p);
			return;
		}
		while (p && strcmp(p->key, params->args[i]) != 0)
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

void	print_env(t_env_var *env_var_list)
{
	t_env_var	*tmp;

	tmp = env_var_list;
	while (tmp)
	{
		if (tmp->value)
			ft_printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
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
	t_env_var	*current;
	t_env_var	*tmp;

	current = env_var_list;
	while (current)
	{
		tmp	= current;
		current = current->next;
		free_env_var_node(tmp);
	}
}
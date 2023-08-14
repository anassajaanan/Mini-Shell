/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:09:05 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/14 17:25:18 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env(t_env_var **env_var_list)
{
	t_env_var	*tmp;

	tmp = *env_var_list;
	while (tmp)
	{
		if (tmp->value)
			ft_printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

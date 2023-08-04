/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:01:18 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/04 16:09:51 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (args == NULL)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	args = NULL;
}

void	free_params(t_params *params)
{
	if (params->line)
		free(params->line);
	if (params->command)
		free(params->command);
	if (params->args)
		free_args(params->args);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:35:20 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/07 15:44:57 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parse_commands_to_queue(t_params *params)
{
	int		i;
	t_cmd	*cmd;

	init_queue(&params->q);
	params->full_command = ft_strtrim(params->line, " \n\t\v\f\r");
	params->commands = ft_split(params->full_command, '|');
	i = 0;
	while (params->commands[i])
	{
		cmd = new_cmd(params->commands[i]);
		enqueue(&params->q, cmd);
		i++;
	}
}
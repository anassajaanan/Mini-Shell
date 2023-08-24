/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:44:47 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/24 13:37:08 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"



void	run_cmd(t_cmd *cmd, t_env_var **env_var_list, int *exit_status)
{
	if (cmd->type == PIPE)
	
}
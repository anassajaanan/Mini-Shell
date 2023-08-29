/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:44:47 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/29 10:45:32 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"

void	run_cmd(t_cmd *cmd, t_env_var **env_var_list, int *exit_status, t_cmd *tree, char *buf)
{
	if (cmd->type == PIPE)
		run_pipe(cmd, env_var_list, exit_status, tree, buf);
	else if (cmd->type == REDIR)
		run_redir(cmd, env_var_list, exit_status, tree, buf);
	else if (cmd->type == EXEC)
		run_exec(cmd, env_var_list, exit_status, tree, buf);
	exit(*exit_status);
}
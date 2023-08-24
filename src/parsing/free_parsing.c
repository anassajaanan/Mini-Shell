/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 08:31:22 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/24 09:36:28 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

void	free_tree(t_cmd *cmd)
{
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;
	t_execcmd	*ecmd;

	if (cmd && cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		free_tree(pcmd->left);
		free_tree(pcmd->right);
		if (pcmd)
			free(pcmd);
	}
	else if (cmd && cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		free_tree(rcmd->subcmd);
		if (rcmd)
			free(rcmd);
	}
	else if (cmd && cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		if (ecmd)
			free(ecmd);
	}
}
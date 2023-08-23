/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:00:08 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/23 19:48:37 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsing.h"

t_cmd	*parse_redir(t_cmd *subcmd, char **ps, char *es)
{
	char	*q;
	char	*eq;
	int		tok;
	t_cmd	*cmd;

	cmd = subcmd;
	if (peek(ps, es, "<>"))
	{
		tok = get_next_token(ps, es, 0, 0);
		get_next_token(ps, es, &q, &eq);
		if (tok == '<')
			cmd = redircmd(parse_redir(subcmd, ps, es),
					redirdata(q, eq, O_RDONLY, 0), '<');
		else if (tok == '>')
			cmd = redircmd(parse_redir(subcmd, ps, es),
					redirdata(q, eq, O_WRONLY | O_CREAT | O_TRUNC, 1), '>');
		else if (tok == '+')
			cmd = redircmd(parse_redir(subcmd, ps, es),
					redirdata(q, eq, O_WRONLY | O_CREAT | O_APPEND, 1), '+');
		else if (tok == '%')
			cmd = redircmd(parse_redir(subcmd, ps, es),
					redirdata(q, eq, O_RDONLY, 0), '%');
	}
	return (cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 15:15:07 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/26 15:15:54 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"

char	*process_quoted_filename(char *file)
{
	int				i;
	t_queue_char	q;

	i = 0;
	init_queue_char(&q);
	while (file[i])
	{
		if (file[i] == '\"')
		{
			i++;
			while (file[i] && file[i] != '\"')
			{
				enqueue_char(&q, file[i]);
				i++;
			}
			if (file[i] == '\"')
				i++;
		}
		else
		{
			enqueue_char(&q, file[i]);
			i++;
		}
	}
	return (queue_char_to_str(&q));
}

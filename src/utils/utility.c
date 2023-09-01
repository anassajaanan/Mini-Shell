/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:45:27 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/01 20:04:42 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/utility.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	is_whitespace_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_whitespace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	forking(t_params *params)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		free_panic_exit(params, "fork", 1);
	return (pid);
}

void	pipe1(int fd[2], t_params *params)
{
	if (pipe(fd) == -1)
		free_panic_exit(params, "pipe", 1);
}

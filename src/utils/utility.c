/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:45:27 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/01 14:46:38 by aajaanan         ###   ########.fr       */
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

void	panic(char *s)
{
	perror(s);
	exit(1);
}

void	panic_exit(int exit_status, char *s)
{
	perror(s);
	exit(exit_status);
}

int	forking(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		panic("fork");
	return (pid);
}

void	pipe1(int fd[2])
{
	if (pipe(fd) == -1)
		panic("pipe");
}

void	free1(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	free_split(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	free_exit(t_params *params, int exit_status)
{
	free1(params->buf);
	free_tree(params->tree);
	free_env_var_list(params->env_var_list);
	free_queue(&params->args_queue);
	exit(exit_status);
}

void	free_panic_exit(t_params *params, char *error, int exit_status)
{
	free1(params->buf);
	free_tree(params->tree);
	free_env_var_list(params->env_var_list);
	free_queue(&params->args_queue);
	perror(error);
	exit(exit_status);
}
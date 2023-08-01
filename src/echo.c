/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:09:05 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/01 21:05:40 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_echo_command(char *command)
{
	int	i;
	int	double_quote;
	int	single_quote;
	
	i = 0;
	double_quote = 0;
	single_quote = 0;
	while (command[i])
	{
		if (command[i] == '"')
			double_quote++;
		if (command[i] == '\'')
			single_quote++;
		i++;
	}
	if (double_quote % 2 != 0)
	{
		printf("Error: Missing closing double quote (\").\n");
		return (0);
	}
	if (single_quote % 2 != 0)
	{
		printf("Error: Missing closing single quote (').\n");
		return (0);
	}
	return (1);
}

void	handle_double_quoted_string(char *command, int *i)
{
	(*i)++;
	while (command[*i] && command[*i] != '"')
	{
		if (command[*i] == '\\')
		{
			(*i)++;
			while (command[*i] && command[*i] == '\\')
				write(1, &command[(*i)++], 1);
		}
		else
			write(1, &command[(*i)++], 1);
	}
	if (command[*i] == '"')
		(*i)++;
}


void	handle_single_quoted_string(char *command, int *i)
{
	(*i)++;
	while (command[*i] && command[*i] != '\'')
		write(1, &command[(*i)++], 1);
	if (command[*i] == '\'')
		(*i)++;
}

void	handle_backslashes_and_spaces(char *command, int *i)
{
	if (command[*i] == '\\')
	{
		(*i)++;
		while (command[*i] && command[*i] == '\\')
			write(1, &command[(*i)++], 1);
	}
	else if (command[*i] == ' ')
	{
		write(1, &command[(*i)++], 1);
		while (command[*i] && command[*i] == ' ')
			(*i)++;
	}
}

void	echo(char *command)
{
	int		i;
	int		new_line;
	
	i = 0;
	new_line = 1;
	if (!is_valid_echo_command(command))
		return ;
	while (command[i] && command[i] == ' ')
		i++;
	if (ft_strncmp(command + i, "-n", 2) == 0)
	{
		new_line = 0;
		i += 2;
		while (command[i] && command[i] == ' ')
			i++;
	}
	while (command[i])
	{
		if (command[i] == '"')
			handle_double_quoted_string(command, &i);
		else if (command[i] == '\'')
			handle_single_quoted_string(command, &i);
		else if (command[i] == '\\' || command[i] == ' ')
			handle_backslashes_and_spaces(command, &i);
		else
			write(1, &command[i++], 1);
	}
	if (new_line)
		write(1, "\n", 1);
}
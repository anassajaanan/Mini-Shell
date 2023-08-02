/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:09:05 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/02 11:00:29 by aajaanan         ###   ########.fr       */
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

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

void	extract_variable_name(char *command, char *variable_name, int *i)
{
	int	j;

	j = 0;
	while (command[*i] && !is_space(command[*i]))
	{
		variable_name[j] = command[*i];
		(*i)++;
		j++;
	}
	variable_name[j] = '\0';
}

void handle_backslashes(char *command, int *i, int inside_quotes)
{
	int	count;

	count = 0;
	while (command[*i] && command[*i] == '\\')
	{
		(*i)++;
		count++;	
	}
	if (inside_quotes && count % 2 == 1)
		count = (count / 2) + 1;
	else
		count = count / 2;
	while (count > 0)
	{
		write(1, "\\", 1);
		count--;
	}
}

void	handle_space(char *command, int *i)
{
	write(1, " ", 1);
	while (command[*i] && command[*i] == ' ')
		(*i)++;
}

void	handle_environment_variable(char *command, int *i)
{
	char	variable_name[250];
	char	*variable_value;

	(*i)++;
	extract_variable_name(command, variable_name, i);
	variable_value = getenv(variable_name);
	if (variable_value)
		ft_printf("%s", variable_value);
}

void	handle_double_quoted_string(char *command, int *i)
{
	(*i)++;
	while (command[*i] && command[*i] != '"')
	{
		if (command[*i] == '\\')
			handle_backslashes(command, i, 1);
		else if (command[*i] == '$')
			handle_environment_variable(command, i);
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




void	echo(char *command)
{
	int		i;
	int		new_line;
	
	i = 0;
	new_line = 1;
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
		else if (command[i] == '$')
			handle_environment_variable(command, &i);
		else if (command[i] == '\\')
			handle_backslashes(command, &i, 0);
		else if (command[i] == ' ')
			handle_space(command, &i);
		else
			write(1, &command[i++], 1);
	}
	if (new_line)
		write(1, "\n", 1);
}
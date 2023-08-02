/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malmessa <malmessa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:09:05 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/02 10:08:19 by malmessa         ###   ########.fr       */
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


void	echo(char *command)
{
	int	i;
	int	count;
	int	new_line;
	
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
		{
			i++;
			while (command[i] && command[i] != '"')
			{
				if (command[i] == 92)
				{
					count = 0;
					while (command[i] && command[i] == 92)
					{
						i++;
						count++;	
					}
					if (count % 2 == 1)
						count = (count / 2) + 1;
					else 
						count = count / 2;
					while (count > 0)
					{
						write(1, "\\", 1);
						count--;
					}
				}
				else
					write(1, &command[i++], 1);
			}
			if (command[i] == '"')
				i++;
		}
		else if (command[i] == '\'')
		{
			i++;
			while (command[i] && command[i] != '\'')
				write(1, &command[i++], 1);
			if (command[i] == '\'')
				i++;
		}
		else if (command[i] == 92)
		{
			count = 0;
			while (command[i] && command[i] == 92)
			{
				i++;
				count++;	
			}
			count = count / 2;
			while (count > 0)
			{
				write(1, "\\", 1);
				count--;
			}
		}
		else if (command[i] == ' ')
		{
			write(1, &command[i++], 1);
			while (command[i] && command[i] == ' ')
				i++;
		}
		else
			write(1, &command[i++], 1);
	}
	if (new_line)
		write(1, "\n", 1);
}
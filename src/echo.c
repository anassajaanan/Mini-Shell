/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:09:05 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/14 12:01:08 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_single_quoted_string(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != '\'')
	{
		ft_printf("%c", str[i]);
		i++;
	}
}

void	handle_double_quoted_string(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$')
		{
			// loop in env variables to find the value of the variable & print it
			ft_printf("ENV");
			//do not forget to skip the variable name after printing it

			// ignore the variable if it does not exit and skip it, print it if it exits
			// we need to have a space after the variable name, otherwise it is not a variable
			// Example: this is a sample input/output, TERM_PROGRAM is a variable but is ignored because it is not followed by a space
			/*
			bash-3.2$ echo "$TERM_PROGRAMcheck"

			bash-3.2$ 
			*/
		}
		else
			ft_printf("%c", str[i]);
		i++;
	}
}

void	echo(char **argv)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
	{
		new_line = 0;
		i++;
	}
	while (argv[i])
	{
		if (argv[i][0] == '\'')
			handle_single_quoted_string(argv[i]);
		else if (argv[i][0] == '\"')
			handle_double_quoted_string(argv[i]);//we need to pass the env variables
		else
			ft_printf("%s", argv[i]);
		if (argv[i + 1])
			ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
}
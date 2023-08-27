/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 19:27:52 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/27 19:30:41 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtins.h"

int	contains_unbalanced_quotes_echo(char *arg)
{
	int		i;
	int		tok;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\"' || arg[i] == '\'')
		{
			tok = arg[i];
			i++;
			while (arg[i] && arg[i] != tok)
				i++;
			if (!arg[i])
				return (1);
			i++;
		}
		else
			i++;
	}
	return (0);
}

int	is_valid_echo_command(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (contains_unbalanced_quotes_echo(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_newline_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-')
	{
		while (str[i] && str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

int	is_newline_flag_quotes(char *str)
{
	int	i;
	int	len;

	if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"' && str[1] == '-')
	{
		i = 2;
		len = ft_strlen(str);
		while (i < len - 1)
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	checking_newline_flag_quotes(int *i, int *new_line, char **argv)
{
	*i = 1;
	*new_line = 1;
	while (argv[*i] && is_newline_flag(argv[*i]))
	{
		new_line = 0;
		(*i)++;
	}
	while (argv[*i] && is_newline_flag_quotes(argv[*i]))
	{
		new_line = 0;
		(*i)++;
	}
}

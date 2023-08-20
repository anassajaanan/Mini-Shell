/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:09:05 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/20 14:17:59 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int contains_unbalanced_quotes(char *arg)
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
	int i;

	i = 1;
	while (argv[i])
	{
		if (contains_unbalanced_quotes(argv[i]))
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

int is_newline_flag_quotes(char *str)
{
	int i;
	int len;

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

char	*get_var_name(char *arg)
{
	int i;

	i = 0;
	if (ft_isdigit(arg[i]))
	{
		int n = arg[i] - '0';
		return (ft_itoa(n));
	}
	while (arg[i] && !ft_strchr(" \t\n\v\f\r\'\"$/=", arg[i]))
		i++;
	return (ft_substr(arg, 0, i));
}

void	echo(char **argv, int *exit_status)
{
	int	i;
	int	new_line;
	
	if (!is_valid_echo_command(argv))
	{
		ft_printf_fd(STDERR_FILENO, "minishell: syntax error: unbalanced quotes\n");
		*exit_status = 258;
		return ;
	}
	i = 1;
	new_line = 1;
	while (argv[i] && is_newline_flag(argv[i]))
	{
		new_line = 0;
		i++;
	}
	while (argv[i] && is_newline_flag_quotes(argv[i]))
	{
		new_line = 0;
		i++;
	}
	while (argv[i])
	{
		char *arg = argv[i];
		if (ft_strcmp(arg, "~") == 0)
		{
			ft_printf("%s", getenv("HOME"));
			i++;
			continue ;
		}
		int j = 0;
		while (arg[j])
		{
			if (arg[j] == '\'')
			{
				j++;
				while (arg[j] && arg[j] != '\'')
				{
					ft_printf("%c", arg[j]);
					j++;
				}
				if (arg[j] == '\'')
					j++;
			}
			else if (arg[j] == '\"')
			{
				j++;
				while (arg[j] && arg[j] != '\"')
				{
					if (arg[j] == '$' && arg[j + 1] == '?')
					{
						ft_printf("%d", *exit_status);
						j += 2;
					}
					else if (arg[j] == '$')
					{
						j++;
						char *var_name = get_var_name(arg + j);
						// ft_printf("{%s}", var_name);
						char *value = getenv(var_name);
						if (value)
							ft_printf("%s", value);
						free(var_name);
						j += ft_strlen(var_name);
					}
					else
					{
						ft_printf("%c", arg[j]);
						j++;
					}
				}
				if (arg[j] == '\"')
					j++;
			}
			else if (arg[j] == '$')
			{
				j++;
				if (arg[j] == '?')
				{
					ft_printf("%d", *exit_status);
					j++;
				}
				else
				{
					char *var_name = get_var_name(arg + j);
					char *value = getenv(var_name);
					if (value)
						ft_printf("%s", value);
					free(var_name);
					j += ft_strlen(var_name);
				}
			}
			else
			{
				ft_printf("%c", arg[j]);
				j++;
			}
		}
		if (argv[i + 1])
			ft_printf(" ");
		i++;
	}
	
	if (new_line)
		ft_printf("\n");
	
}

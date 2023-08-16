/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:09:05 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/16 07:32:34 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	handle_envirement_variable(char *arg, int exit_status)
{
	char	**variables;
	char	*value;
	int		i;
	
	if (ft_strcmp(arg, "$?") == 0)
		ft_printf("%d", exit_status);
	else if (arg[0] == '$')
	{
		i = 0;
		variables = ft_split(arg, '$');
		while (variables[i])
		{
			value = getenv(variables[i]);
			if (value)
				ft_printf("%s", value);
			i++;
		}
		free_args(variables);
	}
}

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

void	handle_double_quoted_string(char *str, int exit_status)
{
	int	i;
	int	j;

	i = 1;
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			ft_printf("%d", exit_status);
			i += 2;
		}
		else if (str[i] == '$')
		{
			
			j = ++i;
			while (!ft_strchr(" $\t\n\v\f\r\"", str[i]))
				i++;
			char *var_name = (char *)malloc(sizeof(char) * (i - j + 1));
			ft_strlcpy(var_name, str + j, i - j + 1);
			char *value = getenv(var_name);
			if (value)
				ft_printf("%s", value);
			free(var_name);
		}
		else
		{
			ft_printf("%c", str[i]);
			i++;
		}
	}
}

void process_argument(char *arg, int exit_status)
{
	if (arg[0] == '\'')
		handle_single_quoted_string(arg);
	else if (arg[0] == '\"')
		handle_double_quoted_string(arg, exit_status);
	else if (arg[0] == '$')
		handle_envirement_variable(arg, exit_status);
	else
		ft_printf("%s", arg);
}

void	echo(char **argv, int exit_status)
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
		process_argument(argv[i], exit_status);
		if (argv[i + 1])
			ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:09:05 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/27 13:16:59 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtins.h"


static int	contains_unbalanced_quotes_echo(char *arg)
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

char	*get_var_name(char *arg)
{
	int	i;
	int	n;

	i = 0;
	if (ft_isdigit(arg[i]))
	{
		n = arg[i] - '0';
		return (ft_itoa(n));
	}
	while (arg[i] && ((ft_isalnum(arg[i]) || arg[i] == '_')))
		i++;
	return (ft_substr(arg, 0, i));
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

void	single_quote(int *j, char *arg)
{
	(*j)++;
	while (arg[*j] && arg[*j] != '\'')
	{
		ft_printf("%c", arg[*j]);
		(*j)++;
	}
	if (arg[*j] == '\'')
		(*j)++;
}

void	double_quote_2(int *j, char *arg, t_env_var *env_var_list)
{
	char	*var_name;
	char	*value;

	(*j)++;
	var_name = get_var_name(arg + *j);
	if (ft_strlen(var_name) == 0)
		ft_printf("$");
	else
	{
		value = getenv_value(var_name, env_var_list);
		if (value)
			ft_printf("%s", value);
		(*j) += ft_strlen(var_name);
	}
	free(var_name);
}

void	double_quote(int *j,
	char *arg, int exit_status, t_env_var *env_var_list)
{
	(*j)++;
	while (arg[*j] && arg[*j] != '\"')
	{
		if (arg[*j] == '$' && arg[(*j) + 1] == '?')
		{
			ft_printf("%d", exit_status);
			(*j) += 2;
		}
		else if (arg[*j] == '$')
			double_quote_2(j, arg, env_var_list);
		else
			ft_printf("%c", arg[(*j)++]);
	}
	if (arg[*j] == '\"')
		(*j)++;
}

void	dollar_sign(int *j, char *arg, int exit_status, t_env_var *env_var_list)
{
	char	*var_name;
	char	*value;

	(*j)++;
	if (arg[*j] == '?')
	{
		ft_printf("%d", exit_status);
		(*j)++;
	}
	else
	{
		var_name = get_var_name(arg + *j);
		if (ft_strlen(var_name) == 0)
			ft_printf("$");
		else
		{
			value = getenv_value(var_name, env_var_list);
			if (value)
				ft_printf("%s", value);
			(*j) += ft_strlen(var_name);
		}
		free(var_name);
	}
}

void	invalid_echo(char **argv)
{
	if (!is_valid_echo_command(argv))
	{
		ft_printf_fd
			(STDERR_FILENO, "minishell: syntax error: unbalanced quotes\n");
		exit(258);
	}
}

void	echo_2(char *arg, t_env_var *env_var_list, int exit_status)
{
	int	j;

	j = 0;
	while (arg[j])
	{
		if (arg[j] == '\'')
			single_quote(&j, arg);
		else if (arg[j] == '\"')
			double_quote(&j, arg, exit_status, env_var_list);
		else if (arg[j] == '$')
			dollar_sign(&j, arg, exit_status, env_var_list);
		else
			ft_printf("%c", arg[j++]);
	}
}

void	echo(char **argv, t_env_var *env_var_list, int exit_status)
{
	int		i;
	int		new_line;
	char	*arg;

	invalid_echo(argv);
	checking_newline_flag_quotes(&i, &new_line, argv);
	while (argv[i])
	{
		arg = argv[i];
		if (ft_strcmp(arg, "~") == 0)
		{
			ft_printf("%s", getenv_value("HOME", env_var_list));
			i++;
			continue ;
		}
		echo_2(arg, env_var_list, exit_status);
		if (argv[i++ + 1])
			ft_printf(" ");
	}
	if (new_line)
		ft_printf("\n");
}
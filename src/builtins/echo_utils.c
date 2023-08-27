/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 19:25:13 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/27 19:33:36 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtins.h"

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

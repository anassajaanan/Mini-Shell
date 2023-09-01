/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 08:11:59 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/01 19:57:37 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtins.h"

static int	is_numeric(const char *str)
{
	if (*str && (*str == '+' || *str == '-'))
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

void	handle_non_numeric_arg(char *arg, t_params *params)
{
	ft_printf("exit\n");
	ft_printf_fd(STDERR_FILENO,
		"minishell: exit: %s: numeric argument required\n", arg);
	free_exit(params, 255);
}

void	handle_too_many_args(t_params *params)
{
	ft_printf("exit\n");
	ft_printf_fd(STDERR_FILENO, "minishell: exit: too many arguments\n");
	free_exit(params, 1);
}

void	exit_command(char **argv, t_params *params)
{
	long long	exit_code;
	int			over_under_flow;

	if (argv[1])
	{
		if (!is_numeric(argv[1]))
			handle_non_numeric_arg(argv[1], params);
		else if (argv[2])
			handle_too_many_args(params);
		else
		{
			ft_printf("exit\n");
			exit_code = ft_atoll(argv[1], &over_under_flow);
			if (over_under_flow)
			{
				ft_printf_fd(STDERR_FILENO,
					"minishell: exit: %s: numeric argument required\n", argv[1]);
				free_exit(params, 255);
			}
			free_exit(params, exit_code);
		}
	}
}

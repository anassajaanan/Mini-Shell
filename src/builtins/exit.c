/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 08:11:59 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/27 13:47:46 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtins.h"


int	is_numeric(const char *str)
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




void	exit_command(char **argv)
{
	int				i;
	t_queue_char	q;
	char			*str;
	char			tok;

	if (argv[1])
	{
		init_queue_char(&q);
		str = argv[1];
		i = 0;
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				tok = str[i];
				i++;
				while (str[i] && str[i] != tok)
				{
					enqueue_char(&q, str[i]);
					i++;
				}
				if (str[i] == tok)
					i++;
			}
			else
			{
				enqueue_char(&q, str[i]);
				i++;
			}
		}
		char *arg = queue_char_to_str(&q);
		if (!is_numeric(arg))
		{
			ft_printf("exit\n");
			ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n", arg);
			free(arg);
			//free
			exit(255);
		}
		else if (argv[2])
		{
			ft_printf("exit\n");
			ft_printf_fd(2, "minishell: exit: too many arguments\n");
			exit(1);
		}
		else
		{

			ft_printf("exit\n");
			char *endptr;
			long long exit_code = strtoll(arg, &endptr, 10);
			if ((exit_code == LLONG_MAX && errno == ERANGE) ||
				(exit_code == LLONG_MIN && errno == ERANGE))
			{
				ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n", arg);
				free(arg);
				exit(255);
			}

			free(arg);
			exit(exit_code);
		}
	}
	else
	{
		ft_printf("exit\n");
		exit(0);
	}
}

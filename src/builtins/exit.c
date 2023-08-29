/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 08:11:59 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/29 09:34:36 by aajaanan         ###   ########.fr       */
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

static void	exit_command_2(char *str, t_queue_char *q)
{
	char	tok;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			tok = str[i++];
			while (str[i] && str[i] != tok)
				enqueue_char(q, str[i++]);
			if (str[i] == tok)
				i++;
		}
		else
			enqueue_char(q, str[i++]);
	}
}

static void	exit_command_3(char *arg, char **argv, t_env_var **env_var_list, t_cmd *tree, char *buf)
{
	if (!is_numeric(arg))
	{
		ft_printf("exit\n");
		ft_printf_fd(2,
			"minishell: exit: %s: numeric argument required\n", arg);
		free(arg);
		free1(buf);
		free_tree(tree);
		free_env_var_list(*env_var_list);
		exit(255);
	}
	else if (argv[2])
	{
		ft_printf("exit\n");
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		free(arg);
		free1(buf);
		free_tree(tree);
		free_env_var_list(*env_var_list);
		exit(1);
	}
}

static void	exit_command_4(char *arg, t_env_var **env_var_list, t_cmd *tree, char *buf)
{
	long long	exit_code;
	int			over_under_flow;

	ft_printf("exit\n");
	exit_code = ft_atoll(arg, &over_under_flow);
	if (over_under_flow)
	{
		ft_printf_fd(2,
			"minishell: exit: %s: numeric argument required\n", arg);
		free(arg);
		free1(buf);
		free_tree(tree);
		free_env_var_list(*env_var_list);
		exit(255);
	}
	free(arg);
	free1(buf);
	free_tree(tree);
	free_env_var_list(*env_var_list);
	exit(exit_code);
}

void	exit_command(char **argv, t_env_var **env_var_list, t_cmd *tree, char *buf)
{
	t_queue_char	q;
	char			*str;
	char			*arg;

	if (argv[1])
	{
		init_queue_char(&q);
		str = argv[1];
		exit_command_2(str, &q);
		arg = queue_char_to_str(&q);
		if (!is_numeric(arg) || argv[2])
			exit_command_3(arg, argv, env_var_list, tree, buf);
		else
			exit_command_4(arg, env_var_list, tree, buf);
	}
	else
	{
		ft_printf("exit\n");
		free1(buf);
		free_tree(tree);
		free_env_var_list(*env_var_list);
		exit(0);
	}
}

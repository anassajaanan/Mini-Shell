/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:09:05 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/29 15:04:51 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtins.h"

static void	echo_2(char *arg, t_env_var *env_var_list, int exit_status)
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

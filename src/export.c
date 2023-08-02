/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:12:36 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/02 12:14:39 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_environment_variables()
{
	extern char	**environ;
	char		**env;

	env = environ;
	while (*env)
	{
		ft_printf("declare -x %s\n", *env);
		env++;
	}
}
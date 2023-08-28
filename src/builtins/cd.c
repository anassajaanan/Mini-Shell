/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:02:21 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/28 09:14:49 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtins.h"

void	cd(char **argv, int *exit_status, t_env_var *env_var_list)
{
	t_queue_char	q;
	char			*path;
	char			*new_path;

	path = argv[1];
	init_queue_char(&q);
	if (path == NULL)
	{
		change_to_home_directory(exit_status, env_var_list);
		update_pwd(env_var_list);
		return ;
	}
	else
		get_new_path(path, exit_status, env_var_list, &q);
	new_path = queue_char_to_str(&q);
	if (chdir(new_path) != 0)
	{
		ft_printf_fd
			(2, "minishell: cd: %s: No such file or directory\n", new_path);
		*exit_status = 1;
	}
	else
		update_pwd(env_var_list);
	free(new_path);
}

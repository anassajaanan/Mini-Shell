/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:49:51 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/02 08:51:12 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

# include "../include/command.h"
# include "../include/env.h"
# include "../include/builtins.h"
# include "../include/colors.h"
# include "../include/execution.h"
# include "../include/parsing.h"
# include "../include/queue.h"
# include "../include/signals.h"
# include "../include/utility.h"
# include "../lib/libft/libft.h"

// #=========================@ process_args.c @===============================#
void			process_args(t_cmd *cmd, t_params *params, int *exit_status);

// #=========================@ helpers.c @====================================#
int	is_built_in_command(t_cmd *tree);
void	execute_built_in_command(t_execcmd *ecmd, t_env_var **env_var_list,
		int *exit_status);
void	save_child_pid(int pid, t_params *params);
void	get_exit_status(t_cmd *tree, t_params *params, int *exit_status,
		int status);
void	cleanup(t_params *params);

#endif // MINISHELL_H
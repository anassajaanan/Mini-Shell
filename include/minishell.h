/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:49:51 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/30 08:29:00 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <limits.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../lib/libft/libft.h"
# include "../include/env.h"
# include "../include/command.h"
# include "../include/queue.h"
typedef struct s_params
{
	char		*buf;
	t_env_var	*env_var_list;
	t_cmd		*tree;
	t_queue		args_queue;
}				t_params;


# include "../include/colors.h"
# include "../include/utility.h"
# include "../include/parsing.h"
# include "../include/execution.h"
# include "../include/builtins.h"
# include "../include/signals.h"

void	process_args(t_cmd *cmd, t_params *params, int *exit_status);

#endif //MINISHELL_H
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:49:51 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/01 20:29:20 by aajaanan         ###   ########.fr       */
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

void			process_args(t_cmd *cmd, t_params *params, int *exit_status);

#endif // MINISHELL_H
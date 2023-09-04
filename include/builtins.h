/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:44:59 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/04 09:37:09 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../include/env.h"
# include "../include/minishell.h"
# include "../lib/libft/libft.h"

// #=====================# echo #=====================#
void	echo(char **argv);

// #=====================# env #=====================#
void	env(char **argv, t_params *params);

// #=====================# export #=====================#
// ******* export_utils.c ******** //
char	*extract_variable_name(char *arg, char *equal_sign);
int		is_valid_variable_name(char *key);
// ******* export.c ******** //
void	export(char **args, t_env_var *env_var_list);
void	export_command(char **args, t_env_var **env_var_list, int *exit_status);

// #=====================# unset #=====================#
void	unset_env_var(char **args, t_env_var **env_var_list, int *exit_status);

// #=====================# cd #=====================#
void	cd(char **argv, int *exit_status, t_env_var *env_var_list);

// #=====================# exit #=====================#
void	exit_command(char **argv, t_params *params);

// #=====================# pwd #=====================#
void	pwd(int *exit_status);

#endif /* BUILTINS_H */
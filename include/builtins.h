/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:44:59 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/27 19:33:25 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../include/env.h"

// #=====================# echo #=====================#
// ******* echo_utils.c ******** //
char	*get_var_name(char *arg);
void	single_quote(int *j, char *arg);
void	double_quote_2(int *j, char *arg, t_env_var *env_var_list);
void	double_quote(int *j, char *arg, int exit_status, t_env_var *env_var_list);
void	dollar_sign(int *j, char *arg, int exit_status, t_env_var *env_var_list);
// ******* echo_helpers.c ******** //
int		contains_unbalanced_quotes_echo(char *arg);
int		is_valid_echo_command(char **argv);
int		is_newline_flag(char *str);
int		is_newline_flag_quotes(char *str);
void	checking_newline_flag_quotes(int *i, int *new_line, char **argv);
// ******* echo.c ******** //
void	echo(char **argv, t_env_var *env_var_list, int exit_status);

// #=====================# env #=====================#
void	env(t_env_var **env_var_list);

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
void	exit_command(char **argv);

// #=====================# pwd #=====================#
void	pwd(int *exit_status);

#endif /* BUILTINS_H */
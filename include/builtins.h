/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:44:59 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/01 14:33:14 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../include/minishell.h"
# include "../lib/libft/libft.h"

// #=====================# echo #=====================#
void	echo(char **argv);

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
// ******* cd_utils.c ******** //
void	handle_single_quote_cd(int *i, char *path, t_queue_char *q);
void	tilde(char **path_and_home_dir, t_queue_char *q, t_env_var *env_var_list, int *i);
void	handle_dollar_sign_cd(char **vars, t_env_var *env_var_list, int *i, t_queue_char *q);
void	handle_double_quotes_2_cd(char *path, t_env_var *env_var_list, t_queue_char *q, int *i);
void	handle_double_quotes_cd(char **vars, t_env_var *env_var_list, t_queue_char *q, int *i);
// ******* cd_helpers.c ******** //
void	change_to_home_directory(int *exit_status, t_env_var *env_var_list);
char	*get_cd_variable_name(char *arg);
void	update_pwd(t_env_var *env_var_list);
char	**get_new_path_2(char *path, int *exit_status, char *home_dir, int i);
void	get_new_path(char *path, int *exit_status, t_env_var *env_var_list, t_queue_char *q);
// ******* cd.c ******** //
void	cd(char **argv, int *exit_status, t_env_var *env_var_list);

// #=====================# exit #=====================#
void	exit_command(char **argv, t_params *params);

// #=====================# pwd #=====================#
void	pwd(int *exit_status);

#endif /* BUILTINS_H */
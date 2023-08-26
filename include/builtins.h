/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 17:44:59 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/26 17:55:15 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	echo(char **argv, t_env_var *env_var_list, int exit_status);
void	env(t_env_var **env_var_list);
void	export_cmd(char **argv, t_env_var **env_var_list, int exit_status);
void	handle_export_command(char **args, t_env_var **env_var_list, int *exit_status);
void	unset_env_var(char **args, t_env_var **env_var_list, int *exit_status);
void	cd(char **argv, int *exit_status, t_env_var *env_var_list);
void	exit_command(char **argv, int *exit_status);
void	pwd(int *exit_status);

#endif /* BUILTINS_H */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:46:52 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/29 09:23:13 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

void	run_cmd(t_cmd *cmd, t_env_var **env_var_list, int *exit_status, t_cmd *tree, char *buf);


void	run_pipe(t_cmd *cmd, t_env_var **env_var_list, int *exit_status, t_cmd *tree, char *buf);


void	run_redir(t_cmd *cmd, t_env_var **env_var_list, int *exit_status, t_cmd *tree, char *buf);
char	*process_quoted_filename(char *file);

void	run_exec(t_cmd *cmd, t_env_var **env_var_list, int *exit_status, t_cmd *tree, char *buf);

#endif /* EXECUTION_H */

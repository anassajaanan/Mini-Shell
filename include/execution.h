/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:46:52 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/27 09:16:27 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

void	run_cmd(t_cmd *cmd, t_env_var **env_var_list, int *exit_status);


void	run_pipe(t_cmd *cmd, t_env_var **env_var_list, int *exit_status);


void	run_redir(t_cmd *cmd, t_env_var **env_var_list, int *exit_status);
char	*process_quoted_filename(char *file);

void	run_exec(t_cmd *cmd, t_env_var **env_var_list, int *exit_status);

#endif /* EXECUTION_H */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:46:28 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/29 15:47:42 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_H
# define UTILITY_H

# include "../include/minishell.h"

int		is_whitespace(char c);
void	panic(char *s);
void	panic_exit(int status, char *s);
int		forking(void);
void	pipe1(int fd[2]);
void	free_split(char **array);
void	free1(void *ptr);

void	free_exit(t_params *params, int exit_status);
void	free_panic_exit(t_params *params, char *error, int exit_status);

#endif // UTILITY_H
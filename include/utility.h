/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:46:28 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/01 20:06:06 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_H
# define UTILITY_H

# include "../include/minishell.h"

// #==================@ utility.c @==================#
int		is_whitespace(char c);
int		is_whitespace_string(char *str);
int		forking(t_params *params);
void	pipe1(int fd[2], t_params *params);

// #==================@ free.c @==================#
void	free_split(char **array);
void	free1(void *ptr);
void	free_exit(t_params *params, int exit_status);
void	free_panic_exit(t_params *params, char *error, int exit_status);

#endif // UTILITY_H
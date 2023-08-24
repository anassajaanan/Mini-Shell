/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:46:28 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/24 13:13:29 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_H
# define UTILITY_H

int		is_whitespace(char c);
void	panic(char *s);
void	panic_exit(int status, char *s);
int		forking(void);
void	pipe1(int fd[2]);

#endif // UTILITY_H
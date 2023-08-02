/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:30:21 by aajaanan          #+#    #+#             */
/*   Updated: 2023/07/12 20:14:33 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>

void	ft_putchar(char c, int *counter);
void	ft_puthex(uintptr_t n, char case_type, int *counter);
void	ft_putnbr(int n, int *counter);
void	ft_putptr(void *ptr, int *counter);
void	ft_putstr(char *str, int *counter);
void	ft_putunbr(unsigned int n, int *counter);
void	handle_format_specifier(va_list args, char c, int *counter);
int		ft_printf(const char *format, ...);

#endif /* FT_PRINTF_H */

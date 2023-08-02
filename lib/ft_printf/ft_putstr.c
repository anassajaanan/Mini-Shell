/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:22:27 by aajaanan          #+#    #+#             */
/*   Updated: 2023/07/04 12:47:54 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(char *str, int *counter)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		write(1, &(*str), 1);
		(*counter)++;
		str++;
	}
}

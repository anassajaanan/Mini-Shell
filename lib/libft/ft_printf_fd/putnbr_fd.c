/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:23:09 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/17 08:01:01 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	putnbr_fd(int fd, int n, int *counter)
{
	if (n == -2147483648)
		putstr_fd(fd, "-2147483648", counter);
	else if (n < 0)
	{
		putchar_fd(fd, '-', counter);
		putnbr_fd(fd, -n, counter);
	}
	else if (n >= 10)
	{
		putnbr_fd(fd, n / 10, counter);
		putnbr_fd(fd, n % 10, counter);
	}
	else
		putchar_fd(fd, n + '0', counter);
}

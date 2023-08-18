/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putunbr_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:27:08 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/17 08:04:03 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	putunbr_fd(int fd, unsigned int n, int *counter)
{
	if (n >= 10)
	{
		putnbr_fd(fd, n / 10, counter);
		putnbr_fd(fd, n % 10, counter);
	}
	else
		putchar_fd(fd, n + '0', counter);
}

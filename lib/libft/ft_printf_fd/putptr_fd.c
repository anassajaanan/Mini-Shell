/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putptr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:24:41 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/17 08:03:12 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	putptr_fd(int fd, void *ptr, int *counter)
{
	if (ptr == NULL)
		putstr_fd(fd, "0x0", counter);
	else
	{
		putstr_fd(fd, "0x", counter);
		puthex_fd(fd, (uintptr_t)ptr, 'x', counter);
	}
}

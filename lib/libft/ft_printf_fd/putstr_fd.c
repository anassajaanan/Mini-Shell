/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:22:27 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/17 07:59:49 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	putstr_fd(int fd, char *str, int *counter)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		write(fd, &(*str), 1);
		(*counter)++;
		str++;
	}
}

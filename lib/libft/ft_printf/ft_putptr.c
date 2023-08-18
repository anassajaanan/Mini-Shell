/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 11:24:41 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/16 17:55:32 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putptr(void *ptr, int *counter)
{
	if (ptr == NULL)
		ft_putstr("0x0", counter);
	else
	{
		ft_putstr("0x", counter);
		ft_puthex((uintptr_t)ptr, 'x', counter);
	}
}

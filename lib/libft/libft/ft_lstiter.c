/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 08:39:01 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/16 17:51:15 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstiter(t_list *head, void (*f)(void *))
{
	if (head == NULL || f == NULL)
		return ;
	while (head)
	{
		f(head->content);
		head = head->next;
	}
}

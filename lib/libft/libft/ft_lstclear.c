/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 08:35:00 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/16 17:51:15 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **head, void (*del)(void *))
{
	t_list	*temp;

	if (head == NULL || del == NULL)
		return ;
	while (*head)
	{
		temp = (*head)->next;
		ft_lstdelone(*head, del);
		*head = temp;
	}
}

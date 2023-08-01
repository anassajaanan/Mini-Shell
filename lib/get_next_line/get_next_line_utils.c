/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:56:35 by aajaanan          #+#    #+#             */
/*   Updated: 2023/07/12 10:48:30 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	init_queue(t_queue *q)
{
	q->front = NULL;
	q->rear = NULL;
}

void	enqueue(t_queue *q, char c)
{
	struct s_queue_node	*new_node;

	new_node = (struct s_queue_node *)malloc(sizeof(struct s_queue_node));
	if (!new_node)
		return ;
	new_node->val = c;
	new_node->next = NULL;
	if (q->front == NULL)
	{
		q->front = new_node;
		q->rear = new_node;
	}
	else
	{
		q->rear->next = new_node;
		q->rear = new_node;
	}
}

char	dequeue(t_queue *q)
{
	char				value;
	struct s_queue_node	*tmp;

	tmp = q->front;
	q->front = q->front->next;
	value = tmp->val;
	free(tmp);
	return (value);
}

int	queue_is_empty(t_queue *q)
{
	if (q->front == NULL)
		return (1);
	return (0);
}

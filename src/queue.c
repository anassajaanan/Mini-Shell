/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:02:46 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/07 15:18:12 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_queue(t_queue *q)
{
	q->front = NULL;
	q->rear = NULL;
}

void	enqueue(t_queue *q, void *val)
{
	t_queue_node	*new_node;

	new_node = (t_queue_node *)malloc(sizeof(t_queue_node));
	if (!new_node)
		return ;
	new_node->val = val;
	new_node->next = NULL;
	if (!q->front)
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

void	*dequeue(t_queue *q)
{
	t_queue_node	*tmp;
	void			*val;

	if (!q->front)
		return (NULL);
	tmp = q->front;
	val = tmp->val;
	q->front = q->front->next;
	free(tmp);
	return (val);
}

int	queue_is_empty(t_queue *q)
{
	if (!q->front)
		return (1);
	return (0);
}
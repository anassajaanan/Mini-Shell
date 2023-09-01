/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 08:56:06 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/30 08:32:43 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

typedef struct s_queue_node
{
	void				*val;
	struct s_queue_node	*next;
}						t_queue_node;

typedef struct s_queue
{
	t_queue_node	*front;
	t_queue_node	*rear;
}					t_queue;

void	init_queue(t_queue *q);
void	enqueue(t_queue *q, void *val);
void	*dequeue(t_queue *q);
char	*queue_to_str(t_queue *q);
void	free_queue(t_queue *q);

#endif //QUEUE_H
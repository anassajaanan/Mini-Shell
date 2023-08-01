/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:16:52 by aajaanan          #+#    #+#             */
/*   Updated: 2023/07/12 10:48:54 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

struct	s_queue_node
{
	char				val;
	struct s_queue_node	*next;
};

typedef struct s_queue
{
	struct s_queue_node	*front;
	struct s_queue_node	*rear;
}						t_queue;

/* QUEUE */
void	init_queue(t_queue *q);
void	enqueue(t_queue *q, char c);
char	dequeue(t_queue *q);
int		queue_is_empty(t_queue *q);

/* GET_NEXT_LINE */
int		contains_newline(t_queue *q);
char	*get_line(t_queue *q);
char	*get_last_line(t_queue *q);
char	*handle_bytes(ssize_t bytes, t_queue *q, char *buffer, int *fd);
char	*get_next_line(int fd);

#endif

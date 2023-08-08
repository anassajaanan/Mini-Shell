/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:16:52 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/07 14:11:44 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

struct	s_queue_node_char
{
	char				val;
	struct s_queue_node_char	*next;
};

typedef struct s_queue_char
{
	struct s_queue_node_char	*front;
	struct s_queue_node_char	*rear;
}						t_queue_char;

/* QUEUE */
void	init_queue_char(t_queue_char *q);
void	enqueue_char(t_queue_char *q, char c);
char	dequeue_char(t_queue_char *q);
int		queue_char_is_empty(t_queue_char *q);

/* GET_NEXT_LINE */
int		contains_newline(t_queue_char *q);
char	*get_line(t_queue_char *q);
char	*get_last_line(t_queue_char *q);
char	*handle_bytes(ssize_t bytes, t_queue_char *q, char *buffer, int *fd);
char	*get_next_line(int fd);

#endif

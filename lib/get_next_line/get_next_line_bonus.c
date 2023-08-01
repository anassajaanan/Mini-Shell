/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:15:30 by aajaanan          #+#    #+#             */
/*   Updated: 2023/07/12 10:45:50 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	contains_newline(t_queue *q)
{
	struct s_queue_node	*tmp;

	tmp = q->front;
	while (tmp)
	{
		if (tmp->val == '\n')
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*get_line(t_queue *q)
{
	int					i;
	char				*line;
	struct s_queue_node	*tmp;

	i = 0;
	tmp = q->front;
	while (tmp && tmp->val != '\n')
	{
		tmp = tmp->next;
		i++;
	}
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (q->front && q->front->val != '\n')
		line[i++] = dequeue(q);
	line[i++] = dequeue(q);
	line[i] = '\0';
	return (line);
}

char	*get_last_line(t_queue *q)
{
	int					i;
	struct s_queue_node	*tmp;
	char				*line;

	i = 0;
	tmp = q->front;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (q->front)
		line[i++] = dequeue(q);
	line[i] = '\0';
	return (line);
}

char	*handle_bytes(ssize_t bytes, t_queue *q, char *buffer, int *fd)
{
	ssize_t	i;

	if (bytes == -1)
	{
		free(buffer);
		return (NULL);
	}
	else if (bytes == 0)
	{
		free(buffer);
		if (queue_is_empty(q))
			return (NULL);
		else
			return (get_last_line(q));
	}
	else
	{
		i = 0;
		while (i < bytes)
			enqueue(q, buffer[i++]);
		free(buffer);
		return (get_next_line(*fd));
	}
}

char	*get_next_line(int fd)
{
	ssize_t				bytes;
	char				*buffer;
	t_data_file			*file_data;
	static t_data_file	hash_table[MAX_FD] = {0};

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	file_data = &hash_table[fd];
	if (file_data->flag == 0)
	{
		init_queue(&file_data->q);
		file_data->flag = 1;
	}
	if (file_data->q.front && contains_newline(&file_data->q))
		return (get_line(&file_data->q));
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	bytes = read(fd, buffer, BUFFER_SIZE);
	return (handle_bytes(bytes, &file_data->q, buffer, &fd));
}

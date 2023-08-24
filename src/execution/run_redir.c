/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:46:22 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/24 17:28:47 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/execution.h"

static char	*get_herdoc_input(char *delimiter)
{
	t_queue	q;
	char	*line;
	int		terminal_fd;

	terminal_fd = open("/dev/tty", O_RDONLY);
	if (terminal_fd < 0)
		panic("open");
	dup2(terminal_fd, STDIN_FILENO);
	close(terminal_fd);
	init_queue(&q);
	while (1)
	{
		ft_printf_fd(STDERR_FILENO, "> ");
		line = get_next_line(0);
		if (line == NULL)
			break;
		if (ft_strlen(line) == ft_strlen(delimiter) + 1 &&
			ft_strncmp(line, delimiter, ft_strlen(line) - 1) == 0)
		{
			free(line);
			break;
		}
		enqueue(&q, line);
	}
	return (queue_to_str(&q));
}

static void	write_herdoc_input(char *herdoc_input)
{
	int	fd;

	fd = open("/tmp/herdoc_input.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		panic("open");
	if (write(fd, herdoc_input, ft_strlen(herdoc_input)) < 0)
		panic("write");
	close(fd);
}

void	run_redir(t_cmd *cmd, t_env_var **env_var_list, int exit_status)
{
	t_redircmd	*rcmd;
	char		*herdoc_input;
	
	rcmd = (t_redircmd *)cmd;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (rcmd->r_type != '%')
	{
		close(rcmd->fd);
		if (open(rcmd->file, rcmd->mode, 0644) < 0)
			panic("open");
	}
	else
	{
		herdoc_input = get_herdoc_input(rcmd->file);
		write_herdoc_input(herdoc_input);
		free(herdoc_input);
		close(rcmd->fd);
		if (open("/tmp/herdoc_input.tmp", rcmd->mode, 0644) < 0)
			panic("open");
	}
	run_cmd(rcmd->subcmd, env_var_list, exit_status);
}
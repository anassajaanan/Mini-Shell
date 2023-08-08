/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:25:57 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/08 11:55:43 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "readline/readline.h"
#include "readline/history.h" 

void pwd()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
        printf("%s\n", cwd);
    } else {
        perror("getcwd");
    }
}

void	cd(char *directory)
{
	if (chdir(directory) != 0)
	{
		perror("chdir");
	}

}

int	fork1()
{
	int	pid;
	
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	return (pid);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_cmd		*cmd;
	t_params	params;
	
	while (1)
	{
		ft_printf(MAG "MyShell$: " reset);
		params.line = get_next_line(0);
		parse_commands_to_queue(&params);

		int num_commands = 0;
		t_queue_node *tmp = params.q.front;
		while (tmp)
		{
			num_commands++;
			tmp = tmp->next;
		}

		
		int fd[num_commands - 1][2];
		for (int i = 0; i < num_commands - 1; i++)
		{
			if (pipe(fd[i]) == -1)
			{
				perror("pipe");
				return (EXIT_FAILURE);
			}
		}

		int pid[num_commands];
		for (int i = 0; i < num_commands; i++)
		{
			pid[i] = fork();
			cmd = (t_cmd *)dequeue(&params.q);
			if (pid[i] == 0)
			{
				for (int j = 0; j < num_commands - 1; j++)
				{
					if (j != i - 1)
						close(fd[j][0]);
					if (j != i)
						close(fd[j][1]);
				}
				
				if (i > 0)
				{
					dup2(fd[i - 1][0], STDIN_FILENO);
					close(fd[i - 1][0]);
				}
				if (i < num_commands - 1)
				{
					dup2(fd[i][1], STDOUT_FILENO);
					close(fd[i][1]);
				}


				int err = execve(cmd->path, cmd->args, envp);
				if (err == -1)
					perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		for (int j = 0; j < num_commands - 1; j++)
		{
			close(fd[j][0]);
			close(fd[j][1]);
		}

		for (int i = 0; i < num_commands; i++)
			waitpid(pid[i], NULL, 0);

		free(params.line);
		free(params.full_command);
		free_args(params.commands);
	}
	return (0);
}

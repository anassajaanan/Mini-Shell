/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:25:11 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/08 14:50:07 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "../lib/libft/libft.h"
#include "../lib/ft_printf/ft_printf.h"
#include "../lib/get_next_line/get_next_line.h"
#include "../include/colors.h"

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}						t_env_var;



typedef struct s_cmd
{
	char	*command;
	char	*path;
	char	**args;
	struct red	**reds;
}			t_cmd;

struct red
{
	int red_type;
	int file_name;
};

// t_cmd cmds[2];

// cmd[1]

// ls -la | grep
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

typedef struct s_params
{
	char		*line;
	char		*full_command;
	char		*command;
	char		**args;
	char		**commands;
	t_queue		q;
	t_env_var	*env_var_list;
}			t_params;


// echo.c
void	echo(char *command);

// export.c
void	print_environment_variables(t_env_var *env_var_list);
void	handle_export_command(t_params *params);

// env_var.c
t_env_var	*env_var_new(char *key, char *value);
void		env_var_add_back(t_env_var **env_var_list, t_env_var *new_node);
void		env_var_insert_sorted(t_env_var **env_var_list, t_env_var *new_node);
void		unset_env_var(t_params *params);
void		print_env(t_env_var *env_var_list);
void		copy_env_to_list(t_env_var **env_var_list);
void		free_env_var_node(t_env_var *node);
void		free_env_var_list(t_env_var *env_var_list);

//utils.c
void	free_args(char **args);
void	free_params(t_params *params);

// queue.c
void	init_queue(t_queue *q);
void	enqueue(t_queue *q, void *val);
void	*dequeue(t_queue *q);
int		queue_is_empty(t_queue *q);

// split.c
char	**split(char *str, char sep);


// cmd.c
t_cmd	*new_cmd(char *command);
void	free_cmd(t_cmd *cmd);
char	*find_cmd_path(char *command);
void	free_cmd_path(char *binary_path);

// cmd_parser.c
void	parse_commands_to_queue(t_params *params);

void	free_binary_path(char *binary_path);
char	*find_binary_path(char *command);
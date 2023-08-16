/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:49:51 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/16 08:15:16 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#include "../lib/libft/libft.h"
#include "../lib/get_next_line/get_next_line.h"
#include "../lib/ft_printf/ft_printf.h"

#include "../include/colors.h"

#define TEMP_FILE_NAME "/tmp/minishell_temp"


// =================== Queue.c ======================//

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
int		queue_is_empty(t_queue *q);


// =================== env_var.c ======================//
typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}						t_env_var;

t_env_var	*env_var_new(char *key, char *value);
void		env_var_insert_sorted(t_env_var **env_var_list, t_env_var *new_node);
// void		unset_env_var(t_params *params);
void		print_env(t_env_var *env_var_list);
void		copy_env_to_list(char **envp, t_env_var **env_var_list);
void		free_env_var_node(t_env_var *node);
void		free_env_var_list(t_env_var *env_var_list);


// =================== echo.c ======================//
void	echo(char **argv, int exit_status);

void	env(t_env_var **env_var_list);


void	free_args(char **args);

// =================== export.c ======================//
void	print_environment_variables(t_env_var *env_var_list);
void	export(char **args, t_env_var *env_var_list);
void	handle_export_command(char **args, t_env_var **env_var_list, int *exit_status);

void	cd(char **args, int *exit_status);

void	unset_env_var(char **args, t_env_var **env_var_list, int *exit_status);
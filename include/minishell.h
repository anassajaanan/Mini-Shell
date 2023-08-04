/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:25:11 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/04 17:50:33 by aajaanan         ###   ########.fr       */
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

typedef struct s_params
{
	char		*line;
	char		*command;
	char		**args;
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
void		copy_env_to_list(t_env_var **env_var_list);
void		free_env_var_node(t_env_var *node);
void		free_env_var_list(t_env_var *env_var_list);

//utils.c
void	free_args(char **args);
void	free_params(t_params *params);
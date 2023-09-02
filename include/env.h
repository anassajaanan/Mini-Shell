/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:56:21 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/02 17:08:53 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}						t_env_var;

// ┌───────────────────────────────────┐
// │             env_var.c             │
// └───────────────────────────────────┘
t_env_var				*env_var_new(char *key, char *value);
int						env_var_update_value(t_env_var *env_var_list,
							t_env_var *new_nod);
void					env_var_insert_sorted(t_env_var **env_var_list,
							t_env_var *new_node);
void					init_env_var_list(char **envp,
							t_env_var **env_var_list);
char					*getenv_value(char *key, t_env_var *env_var_list);

// ┌───────────────────────────────────┐
// │          env_var_utils.c          │
// └───────────────────────────────────┘

void					free_env_var_node(t_env_var *node);
void					free_env_var_list(t_env_var *env_var_list);
char					*getenv_value(char *key, t_env_var *env_var_list);

#endif /* ENV_H */
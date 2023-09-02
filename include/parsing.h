/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:34:12 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/02 12:06:38 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../lib/libft/libft.h"

// ┌──────────────────────────────────┐
// │         token_helpers.c          │
// └──────────────────────────────────┘
int		get_next_token(char **ps, char *es, char **q, char **eq);
int		peek(char **ps, char *es, char *tokens);

// ┌─────────────────────────────┐
// │         validate.c          │
// └─────────────────────────────┘
int		validate_syntax(char *buf, int *exit_status);
int		contains_unbalanced_quotes(char *buf, int *exit_status);
int		validate_command(char *buf, int *exit_status);

// ┌───────────────────────────────────┐
// │         validate_helpers.c        │
// └───────────────────────────────────┘
int		check_invalid_pipe_syntax(char **ps, char *es, int *exit_status);
int		validate_redirection(char **ps, char *es, int *exit_status);
int		validate_pipe(char **ps, char *es, int *exit_status);

// ┌───────────────────────────────────┐
// │            parsing.c              │
// └───────────────────────────────────┘
t_cmd	*parse_cmd(char *buf, int *exit_status);
t_cmd	*parse_pipe(char **ps, char *es, int *error);
t_cmd	*parse_exec(char **ps, char *es, int *error);
t_cmd	*parse_redir(t_cmd *subcmd, char **ps, char *es);

// ┌───────────────────────────────────┐
// │       free_parsing.c              │
// └───────────────────────────────────┘
void	free_tree(t_cmd *cmd);

// ┌───────────────────────────────────┐
// │       null_terminate.c            │
// └───────────────────────────────────┘
t_cmd	*null_terminate_command(t_cmd *cmd);

// ┌───────────────────────────────────┐
// │          process_args.c           │
// └───────────────────────────────────┘
int		contains_special_char(char *arg);
char	*getvar_name(char *arg);
void	process_single_quote(char *arg, int *i, t_queue_char *q);
void	process_double_quote_2(int *values[2], char *arg, t_queue_char *q,
			t_params *params);
void	process_double_quote_3(int *values[2], t_queue_char *q);
void	process_double_quote(int *values[2], char *arg, t_queue_char *q,
			t_params *params);
void	process_dollar_sign_2(int *values[2], t_queue_char *q, char *arg,
			t_params *params);
void	process_dollar_sign(int *values[2], t_queue_char *q, char *arg,
			t_params *params);
void	process_args(t_cmd *cmd, t_params *params, int *exit_status);

#endif /* PARSING_H */
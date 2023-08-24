/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:34:12 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/24 10:25:48 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// ┌──────────────────────────────────┐
// │         token_helpers.c          │
// └──────────────────────────────────┘
int	get_next_token(char **ps, char *es, char **q, char **eq);
int	peek(char **ps, char *es, char *tokens);

// ┌─────────────────────────────┐
// │         validate.c          │
// └─────────────────────────────┘
int	validate_syntax(char *buf, int *exit_status);
int	contains_unbalanced_quotes(char *buf, int *exit_status);
int	validate_command(char *buf, int *exit_status);

// ┌───────────────────────────────────┐
// │         validate_helpers.c        │
// └───────────────────────────────────┘
int	check_invalid_pipe_syntax(char **ps, char *es, int *exit_status);
int	validate_redirection(char **ps, char *es, int *exit_status);
int	validate_pipe(char **ps, char *es, int *exit_status);


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

#endif /* PARSING_H */
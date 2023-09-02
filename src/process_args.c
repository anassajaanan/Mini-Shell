/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 08:07:26 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/02 10:09:04 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*getvar_name(char *arg)
{
	int i;

	i = 0;
	if (ft_isdigit(arg[i]))
	{
		int n = arg[i] - '0';
		return (ft_itoa(n));
	}
	while (arg[i] && ((ft_isalnum(arg[i]) || arg[i] == '_')))
		i++;
	return (ft_substr(arg, 0, i));
}

char	*get_clean_arg(char *arg, t_params *params, int *exit_status)
{
	int				i;
	t_queue_char	q;
	char			*clean_arg;
	
	i = 0;
	init_queue_char(&q);
	if (ft_strcmp(arg, "~") == 0)
	{
		clean_arg = ft_strdup(getenv_value("HOME", params->env_var_list));
		enqueue(&params->args_queue, clean_arg);
		return (clean_arg);
	}
	while (arg[i])
	{
		if (arg[i] == '\'')
		{
			i++;
			while (arg[i] && arg[i] != '\'')
			{
				enqueue_char(&q, arg[i]);
				i++;
			}
			i++;
		}
		else if (arg[i] == '\"')
		{
			i++;
			while (arg[i] && arg[i] != '\"')
			{
				if (arg[i] == '$' && (is_whitespace(arg[i + 1]) || arg[i + 1] == '\"'))
				{
					enqueue_char(&q, '$');
					i++;
				}
				else if (arg[i] == '$' && arg[i + 1] == '?')
				{
					char *exit_status_str = ft_itoa(*exit_status);
					enqueue_str(&q, exit_status_str);
					free(exit_status_str);
					i += 2;
				}
				else if (arg[i] == '$')
				{
					i++;
					char *var_name = getvar_name(arg + i);
					char *var_value = getenv_value(var_name, params->env_var_list);
					if (var_value)
						enqueue_str(&q, var_value);
					i += ft_strlen(var_name);
					free1(var_name);
				}
				else
				{
					enqueue_char(&q, arg[i]);
					i++;
				}
			}
			i++;
		}
		else if (arg[i] == '$')
		{
			i++;
			if (!arg[i] || is_whitespace(arg[i]))
			{
				enqueue_char(&q, '$');
				continue ;
			}
			else if (arg[i] == '?')
			{
				char *exit_status_str = ft_itoa(*exit_status);
				enqueue_str(&q, exit_status_str);
				free(exit_status_str);
				i++;
			}
			else
			{
				char *var_name = getvar_name(arg + i);
				char *var_value = getenv_value(var_name, params->env_var_list);
				if (var_value)
					enqueue_str(&q, var_value);
				i += ft_strlen(var_name);
				free1(var_name);
			}
		}
		else
		{
			enqueue_char(&q, arg[i]);
			i++;
		}
	}
	clean_arg = queue_char_to_str(&q);
	enqueue(&params->args_queue, clean_arg);
	return (clean_arg);
}

int	contains_special_char(char *arg)
{
	if (ft_strchr(arg, '\'') || ft_strchr(arg, '\"') || ft_strchr(arg, '$') || ft_strchr(arg, '~'))
		return (1);
	return (0);
}

void	process_args(t_cmd *cmd, t_params *params, int *exit_status)
{
	int			i;
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;
	t_execcmd	*ecmd;

	if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		process_args(pcmd->left, params, exit_status);
		process_args(pcmd->right, params, exit_status);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		if (rcmd->r_type != '%' && contains_special_char(rcmd->file))
			rcmd->file = get_clean_arg(rcmd->file, params, exit_status);
		process_args(rcmd->subcmd, params, exit_status);
	}
	else if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		i = 0;
		while (ecmd->argv[i])
		{
			if (contains_special_char(ecmd->argv[i]))
				ecmd->argv[i] = get_clean_arg(ecmd->argv[i], params, exit_status);
			i++;
		}
	}
}
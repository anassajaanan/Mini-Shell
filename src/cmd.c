/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:49:42 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/07 17:33:43 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cmd	*new_cmd(char *command)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = split(command, ' ');
	cmd->command = ft_strdup(cmd->args[0]);
	cmd->path = find_cmd_path(cmd->command);
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	free(cmd->command);
	free(cmd->path);
	free_args(cmd->args);
	free(cmd);
}

void	free_cmd_path(char *binary_path)
{
	free(binary_path);
	binary_path = NULL;
}

char	*find_cmd_path(char *command)
{
	int		i;
	char	*cmd;
	char	**paths;
	char	*binary_path;
	
	paths = ft_split(getenv("PATH"), ':');
	cmd = ft_strjoin("/", command);
	i = 0;
	while (paths[i])
	{
		binary_path = ft_strjoin(paths[i], cmd);
		if (access(binary_path, X_OK) == 0)
			break;
		free_cmd_path(binary_path);
		i++;
	}
	free(cmd);
	free_args(paths);
	return (binary_path);
}


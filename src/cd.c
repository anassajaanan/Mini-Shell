/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:02:21 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/21 14:57:28 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	change_to_home_directory(int *exit_status, t_env_var *env_var_list)
{
	char	*home_dir;
	
	home_dir = getenv_value("HOME", env_var_list);
	if (home_dir)
	{
		if (chdir(home_dir) != 0)
		{
			perror("cd");
			*exit_status = 1;
		}
	}
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		*exit_status = 1;
	}
}

// void	change_to_directory(char *directory, int *exit_status)
// {
// 	if (chdir(directory) != 0)
// 	{
// 		ft_putstr_fd("minishell: cd: ", 2);
// 		ft_putstr_fd(directory, 2);
// 		ft_putstr_fd(": No such file or directory\n", 2);
// 		*exit_status = 1;
// 	}
// }

// void	expand_tilde(char	*path, int *exit_status)
// {
// 	char	*new_path;
	
// 	if (ft_strcmp(path, "~") == 0)
// 		change_to_home_directory(exit_status);
// 	else if (path[0] == '~')
// 	{
// 		new_path = ft_strjoin(getenv("HOME"), path + 1);
// 		if (chdir(new_path) != 0)
// 		{
// 			if (ft_strcmp(getenv("USER"), path + 1) == 0)
// 				change_to_home_directory(exit_status);
// 			else
// 			{
// 				ft_putstr_fd("minishell: cd: ", 2);
// 				ft_putstr_fd(path + 1, 2);
// 				ft_putstr_fd(": No such file or directory\n", 2);
// 				*exit_status = 1;
// 			}
// 		}
// 		free(new_path);
// 	}
// }

// void	expand_environment_variables(char *path, int *exit_status)
// {
// 	char	*env_var;

// 	env_var = getenv(path + 1);
// 	if (env_var)
// 		change_to_directory(env_var, exit_status);
// 	else
// 		change_to_home_directory(exit_status);
// }

// void	cd(char **args, int *exit_status)
// {
// 	if (args[1] == NULL)
// 		change_to_home_directory(exit_status);
// 	else
// 	{
// 		if (ft_strcmp(args[1], "~") == 0)
// 			change_to_home_directory(exit_status);
// 		else if (args[1][0] == '~')
// 			expand_tilde(args[1], exit_status);
// 		else if (args[1][0] == '$')
// 			expand_environment_variables(args[1], exit_status);
// 		else
// 			change_to_directory(args[1], exit_status);
// 	}
// }


static char	*get_variable_name(char *arg)
{
	int i;

	i = 0;
	while (arg[i] && ((ft_isalnum(arg[i]) || arg[i] == '_')))
		i++;
	return (ft_substr(arg, 0, i));
}

char	*queue_to_str(t_queue_char *q)
{
	int 						i;
	char						*path;
	struct s_queue_node_char	*tmp;

	i = 0;
	tmp = q->front;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	path = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (q->front)
		path[i++] = dequeue_char(q);
	path[i] = '\0';
	return (path);
}


void	update_pwd(t_env_var *env_var_list)
{
	char		*pwd;
	t_env_var	*tmp;
	
	pwd = getcwd(NULL, 0);
	// ft_printf("pwd is : %s\n", pwd);
	tmp = env_var_list;
	while (tmp)
	{
		if (strcmp(tmp->key, "PWD") == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(pwd);
			free(pwd);
			return ;
		}
		tmp = tmp->next;
	}
}

void	cd(char **argv, int *exit_status, t_env_var *env_var_list)
{
	int				i;
	t_queue_char	q;
	char			*path;

	path = argv[1];
	init_queue_char(&q);
	if (path == NULL)
	{
		change_to_home_directory(exit_status, env_var_list);
		update_pwd(env_var_list);
		return;
	}
	else
	{
		i = 0;
		while (path[i])
		{
			if (path[i] == '\'')
			{
				i++;
				while (path[i] && path[i] != '\'')
				{
					enqueue_char(&q, path[i]);
					i++;
				}
				if (path[i] == '\'')
					i++;
			}
			else if (path[i] == '\"')
			{
				i++;
				while (path[i] && path[i] != '\"')
				{
					if (path[i] == '$' && path[i + 1] == '?')
					{
						char *exit_status_str = ft_itoa(*exit_status);
						enqueue_str(&q, exit_status_str);
						free(exit_status_str);
						i += 2;
					}
					else if (path[i] == '$')
					{
						i++;
						char *var_name = get_variable_name(path + i);
						char *var_value = getenv_value(var_name, env_var_list);
						if (var_value)
							enqueue_str(&q, var_value);
						i += ft_strlen(var_name);
						free(var_name);
					}
					else
					{
						enqueue_char(&q, path[i]);
						i++;
					}
				}
				if (path[i] == '\"')
					i++;
			}
			else if (path[i] == '$')
			{
				i++;
				if (path[i] == '?')
				{
					char *exit_status_str = ft_itoa(*exit_status);
					enqueue_str(&q, exit_status_str);
					free(exit_status_str);
					i++;
				}
				else
				{
					char *var_name = get_variable_name(path + i);
					char *var_value = getenv_value(var_name, env_var_list);
					if (var_value)
						enqueue_str(&q, var_value);
					i += ft_strlen(var_name);
					free(var_name);
				}
			}
			else if (path[i] == '~')
			{
				char	*home_dir = getenv_value("HOME", env_var_list);
				if (home_dir)
				{
					enqueue_str(&q, home_dir);
					i++;
				}
				else
				{
					enqueue_char(&q, path[i]);
					i++;
				}
			}
			else
			{
				enqueue_char(&q, path[i]);
				i++;
			}
			
		}
	}
	//print queue
	// ft_printf("the path is : \n");
	// while (q.front)
	// {
	// 	ft_printf("%c", dequeue_char(&q));
	// }
	// ft_printf("\n\n");
	char	*new_path = queue_to_str(&q);
	if (chdir(new_path) != 0)
	{
		ft_printf_fd(2, "minishell: cd: %s: No such file or directory\n", new_path);
		*exit_status = 1;
	}
	else
		update_pwd(env_var_list);
	free(new_path);

	
}
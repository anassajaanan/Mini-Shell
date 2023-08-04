/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:25:57 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/04 14:29:01 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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


int main(void)
{
	t_params	params;
	
	params.env_var_list = NULL;
	copy_env_to_list(&params.env_var_list);
	while (1)
	{
		ft_printf(MAG "MyShell$ " reset);
		params.line = get_next_line(0);
		params.command = ft_strtrim(params.line, " \n\t\v\f\r");
		params.args = ft_split(params.command, ' ');
		if (ft_strncmp(params.command, "exit", 4) == 0)
			break;
		if (ft_strncmp(params.command, "echo ", 5) == 0)
			echo(params.command + 5);
		if (params.args && strcmp(params.args[0], "export") == 0)
			handle_export_command(&params);
		free(params.line);
		free_args(params.args);
		free(params.command);
	}
	free_env_var_list(params.env_var_list);
}
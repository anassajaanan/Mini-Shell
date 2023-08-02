/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:25:57 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/02 12:26:52 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/colors.h"

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



void	free_args(char **args)
{
	int	i;

	i = 0;
	if (args == NULL)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	args = NULL;
}


int main(void)
{
	char	*line;
	char	*command;
	char	**args;
	
	while (1)
	{
		ft_printf(MAG "MyShell$ " reset);
		line = get_next_line(0);
		command = ft_strtrim(line, " \n\t\v\f\r");
		args = ft_split(command, ' ');
		if (ft_strncmp(command, "echo ", 5) == 0)
			echo(command + 5);
		if (args && strcmp(args[0], "export") == 0)
		{
			if (args[1] == NULL)
				print_environment_variables();
		}
		free(line);
		free(args);
		free(command);
	}
}
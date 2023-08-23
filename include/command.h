/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 09:09:23 by aajaanan          #+#    #+#             */
/*   Updated: 2023/08/23 10:34:54 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# define EXEC 1
# define REDIR 2
# define PIPE 3

# define MAXARGS 1024

typedef struct s_cmd
{
	int		type;
}			t_cmd;

typedef struct s_pipecmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}			t_pipecmd;

typedef struct s_execcmd
{
	int		type;
	char	*argv[MAXARGS];
	char	*eargv[MAXARGS];
}			t_execcmd;

typedef struct s_redircmd
{
	int		type;
	char	*file;
	char	*efile;
	int		fd;
	int		mode;
	char	r_type;
	t_cmd	*subcmd;
}			t_redircmd;

typedef struct s_redirdata
{
	char	*file;
	char	*efile;
	int		fd;
	int		mode;
}			t_redirdata;

t_cmd		*pipecmd(t_cmd *left, t_cmd *right);
t_cmd		*execcmd(void);
t_redirdata	redirdata(char *file, char *efile, int mode, int fd);
t_cmd		*redircmd(t_cmd *subcmd, t_redirdata data, char r_type);

#endif // COMMAND_H
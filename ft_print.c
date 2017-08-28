/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 19:41:19 by rfabre            #+#    #+#             */
/*   Updated: 2017/08/28 03:08:54 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *print_pwd(void)
{
	char tmp[1024 + 1];
	char *cwd;

	cwd = getcwd(tmp, 1024);
	return (cwd);
}

void exec_echo(char **commands)
{
	int i;
	int do_new_line;

	do_new_line = 1;
	i = 1;
	if (ft_strequ(commands[1], "-n"))
	{
		do_new_line = 0;
		i++;
	}
	while (commands[i])
	{
		if ((do_new_line == 1 && i > 1) || i > 2)
			ft_putstr(" ");
		ft_putstr(commands[i]);
		i++;
	}
	if (do_new_line)
		ft_putstr("\n");
}


static int check_cd(char **commands, t_env **venv)
{
	if (commands[2])
	{
		ft_putendl("Usage : cd <directory>");
		return (9);
	}
	if (!ft_strncmp(commands[1], "~", 1))
	{
		if (find_str_t_env(venv, "HOME="))
			return (1);
		else
			ft_putendl("'HOME' variable not found");
	}
	if (!ft_strncmp(commands[1], "--", 2))
	{
		if (find_str_t_env(venv, "HOME="))
			return (1);
		else
			ft_putendl("'HOME' variable not found");
	}
	if (!ft_strncmp(commands[1], "-", 1))
	{
		if (find_str_t_env(venv, "OLDPWD="))
			return (2);
		else
			ft_putendl("'OLDPWD' variable not found");
	}
	return (9);
}

static int parse_cd(char **commands, t_env **venv)
{
	int ret;
	ret = check_cd(commands, venv);

	if (ret == 1)
	{
		ft_bzero(commands[1], ft_strlen(commands[1]));
		commands[1] = ft_strsub(get_venv_value(venv, "HOME"), 5,
				ft_strlen(get_venv_value(venv, "HOME=")) - 4);
	}
	else if (ret == 2)
	{
		ft_bzero(commands[1], ft_strlen(commands[1]));
		commands[1] = ft_strsub(get_venv_value(venv, "OLDPWD"), 7,
				ft_strlen(get_venv_value(venv, "OLDPWD=")) - 6);
	}
	else if (ret == 9)
		return (1);
	return (0);
}

void exec_cd(char **cmd, t_env **venv)
{
	char tmp[1024 + 1];
	char *cwd;
	char *oldpwd;
	int  ret;

	ret = parse_cd(cmd, venv);
	oldpwd = getcwd(tmp, 1024);
	if ((!access(cmd[1], 1)) && chdir(cmd[1]) == 0 && !ret)
	{
		ft_modify_tenv(venv, "OLDPWD=", oldpwd);
		ft_putstr("directory changed to : ");
		ft_putendl(cmd[1]);
		cwd = getcwd(tmp, 1024);
		ft_modify_tenv(venv, "PWD=", cwd);
	}
	else
		perror(cmd[1]);
}

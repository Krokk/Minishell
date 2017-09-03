/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 19:41:19 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/03 20:52:00 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_size(char **commands, int mode)
{
	int		i;

	if (mode == 1)
	{
		i = 0;
		while (commands[i])
			i++;
		return (i);
	}
	if (mode == 2)
	{
		ft_putendl("'OLDPWD' variable not found");
		return (5);
	}
	return (0);
}

int			check_cd(char **command, t_env **venv, int size)
{
	if (size == 1 || ft_strequ(command[1], "--") || ft_strequ(command[1], "~"))
	{
		if (find_t_env_strr(venv, "HOME"))
			return (1);
		else
		{
			ft_putendl("'HOME' variable not found");
			return (5);
		}
	}
	else if (ft_strequ(command[1], "-"))
	{
		if (find_t_env_strr(venv, "OLDPWD"))
			return (2);
		else
			return (get_size(command, 2));
	}
	else if (!(ft_strncmp(command[1], "~/", 2)))
	{
		if (find_t_env_strr(venv, "HOME"))
			return (3);
	}
	else if (!(ft_strncmp(command[1], "~", 1)))
		return (4);
	return (0);
}

char		*parse_cd(int ret, t_env **venv, char **commands)
{
	char	*tmp;
	char	*tmpp;

	if (ret == 1)
		return (ft_strsub(get_venv_value(venv, "HOME"), 5,
					ft_strlen(get_venv_value(venv, "HOME")) - 5));
	else if (ret == 2)
	{
		return (ft_strsub(get_venv_value(venv, "OLDPWD"), 7,
					ft_strlen(get_venv_value(venv, "OLDPWD")) - 6));
	}
	if (ret == 3)
	{
		tmpp = ft_strsub(get_venv_value(venv, "HOME"), 5,
					ft_strlen(get_venv_value(venv, "HOME")) - 5);
		tmp = ft_freejoinstr(tmpp, "/");
		return (ft_freejoinstr(tmp, (commands[1] + 1)));
	}
	if (ret == 4)
		return (ft_strjoin("/Users/", (commands[1] + 1)));
	if (ret == 0)
		return (ft_strdup(commands[1]));
	else
		return (NULL);
}

void		do_cd(char *path, t_env **venv)
{
	char	tmp[1024 + 1];
	char	*cwd;
	char	*oldpwd;

	oldpwd = getcwd(tmp, 1024);
	if (!access(path, F_OK))
	{
		if (chdir(path) == 0)
		{
			ft_modify_tenv(venv, "OLDPWD=", oldpwd);
			cwd = getcwd(tmp, 1024);
			ft_modify_tenv(venv, "PWD=", cwd);
		}
		else
			ft_error(2, venv, "Permission denied");
	}
	else
		ft_error(3, venv, path);
}

void		exec_cd(char **cmd, t_env **venv)
{
	int		ret;
	int		size;
	char	*path;

	size = get_size(cmd, 1);
	if (size != 2 && size != 1)
		ft_putendl("usage : cd <directory>");
	else
	{
		ret = check_cd(cmd, venv, size);
		path = parse_cd(ret, venv, cmd);
		if (path != NULL)
			do_cd(path, venv);
		if (ret != 5)
			free(path);
	}
}

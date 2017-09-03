/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 21:22:31 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/03 04:39:00 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **t_env_to_array(t_env **venv)
{
	int i;
	char **result;
	t_env *tmp;
	int j;

	j = 0;
	tmp = *venv;
	while (*venv)
	{
		j++;
		venv = &(*venv)->next;
	}
	if (tmp != NULL)
	{
		if (!(result = ft_memalloc(sizeof(char**) * (j + 1))))
			return (NULL);
		i = -1;
		while (tmp)
		{
			result[++i] = ft_strdup(tmp->content);
			tmp = tmp->next;
		}
		return (result);
	}
	return (NULL);
}

int parse_target(char **commands)
{
	char *tmp;

	if (commands != NULL)
	{
		if (!ft_strncmp(*commands, "./", 2) || !ft_strncmp(*commands, "/", 1))
				return (0);
		else
		{
			tmp = ft_strjoin("/", commands[0]);
			ft_strdel(&commands[0]);
			commands[0] = tmp;
			return (1);
		}
	}
	return (0);
}

void		ft_execcommands(char *path, char **commands, t_env **venv)
{
	pid_t	pid;
	char    **array;

	array = t_env_to_array(venv);
	if ((pid = fork()) == -1)
		ft_error(0, venv, "Fork failed");
	while (1)
	{
		if (pid == 0)
		{
			execve(path, commands, array);
		}
		if (pid > 0)
		{
			wait(0);
			break ;
		}
	}
	ft_freearraystr(array);
}

int ft_access_chk(char *path, t_env **venv)
{
	struct stat s;

	if (!access(path, F_OK))
	{
		if (lstat(path, &s) != -1 && !(S_ISDIR(s.st_mode)) && !access(path, X_OK))
			return (0);
		else
			ft_error(2, venv, "Permission denied");
	}
	return (1);
}

int found_binary(char **path, char **commands, t_env **venv, int ret)
{
	int i;
	char *tmpp;

	i = 0;
	while (path[i])
	{
		tmpp = ft_strjoin(path[i], commands[0]);
		if (!(ft_access_chk(tmpp, venv)) && ret == 1)
			{
				ft_execcommands(tmpp, commands, venv);
				free (tmpp);
				return (1);
			}
		else if (!(ft_access_chk(commands[0], venv)) && ret == 0)
			{
				ft_execcommands(commands[0], commands, venv);
				free (tmpp);
				return (1);
			}
		i++;
		free (tmpp);
	}
	return (0);
}

void look_for_binary(char **commands, t_env **venv)
{
	t_env *tmp;
	char **path;
	int ret;
	int found;

	found = 0;
	tmp = *venv;
	ret = parse_target(&commands[0]);
	while (tmp)
	{
		if (find_t_env_str(tmp->content, "PATH"))
		{
			path = ft_strsplit(tmp->content + 5, ':');
			found = found_binary(path, commands, venv, ret);
			if (found)
			{
				ft_freearraystr(path);
				break;
			}
			ft_freearraystr(path);
		}
		tmp = tmp->next;
	}
	if (found == 0)
		ft_putendl("Command not recognized");
}

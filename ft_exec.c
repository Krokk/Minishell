/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 21:22:31 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/01 01:50:47 by rfabre           ###   ########.fr       */
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
}

void look_for_binary(char **commands, t_env **venv)
{
	t_env *tmp;
	char **path;
	int i;
	int ret;
	char *tmpp;

	i = 0;
	tmp = *venv;
	ret = parse_target(&commands[0]);
	while (tmp)
	{
		if (find_t_env_str(tmp->content, "PATH"))
		{
			path = ft_strsplit(tmp->content + 5, ':');
			while (path[i])
			{
				tmpp = ft_strjoin(path[i], commands[0]);
				if (!(access(tmpp, 1)) && ret == 1)
					{
						ft_execcommands(tmpp, commands, venv);
						free (tmpp);
						break ;
					}
				if (!(access(commands[0], 1)) && ret == 0)
					{
						ft_execcommands(commands[0], commands, venv);
						break ;
					}
				i++;
				free (tmpp);
			}
			ft_freearraystr(path);
		}
		tmp = tmp->next;
	}
}

void		ft_execcommands(char *path, char **commands, t_env **venv)
{
	pid_t	pid;
	char    **array;

	array = t_env_to_array(venv);
	pid = fork();
	while (1)
	{
		if (pid == 0)
		{
			wait(&pid);
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

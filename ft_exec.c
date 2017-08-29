/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 21:22:31 by rfabre            #+#    #+#             */
/*   Updated: 2017/08/30 00:58:33 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **t_env_to_array(t_env **venv)
{
	int i;
	char **result;
	t_env *tmp;

	i = 0;
	tmp = *venv;
	while (*venv)
	{
		i++;
		venv = &(*venv)->next;
	}
	if (tmp != NULL)
	{
		if (!(result = (char**)malloc(sizeof(result) * i + 1)))
			return (NULL);
		i = -1;
		while (tmp)
		{
			result[++i] = ft_strdup(tmp->content);
			tmp = tmp->next;
		}
		result[i] = NULL;
		return (result);
	}
	return (NULL);
}

// TROUVER LE BINAIRE EN CHERCHAMT DANS LES DIFFERENT PATH, FAIRE UN ACCESS, RENVOYER UN CHAR* a execve
int parse_target(char **commands)
{
	if (commands != NULL)
	{
		if (!ft_strncmp(*commands, "./", 2) || !ft_strncmp(*commands, "/", 1))
			{
				return (0);
			}
		else
		{
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

	i = 0;
	tmp = *venv;
	ret = parse_target(&commands[0]);
	if (ret)
		commands[0] = ft_strjoinnfree("/", commands[0], 2, 2);
	while (tmp)
	{
		if (find_t_env_str(tmp->content, "PATH"))
		{
			path = ft_strsplit(tmp->content + 5, ':');
			while (path[i])
			{
				if (!(access((ft_strjoinnfree(path[i], commands[0], ft_strlen(commands[0]), 2)), 1)) && ret == 1)
					{
						ft_putendl("trouver");
						ft_execcommands((ft_strjoin(path[i], commands[0])), commands, venv);
						break ;
					}
				if (!(access(commands[0], 1)) && ret == 0)
					{
						ft_execcommands(commands[0], commands, venv);
						break ;
					}
				i++;
			}
		}
		tmp = tmp->next;
	}
}

void		ft_execcommands(char *path, char **commands, t_env **venv)
{
	pid_t	pid;
	char    **array;

	pid = fork();

	array = t_env_to_array(venv);
	while (1)
	{
		if (pid == 0)
		{
			wait(&pid);
			execve(path, commands, array);
			exit(0);
		}
		if (pid > 0)
		{
			wait(0);
			break ;
		}
	}
}

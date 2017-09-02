/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 21:21:33 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/02 21:11:04 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **new_array(char **commands, int trim,t_env **venv)
{
	int offset;
	int i;
	char **array;

	i = 0;
	offset = 0;
	while (commands[i])
		i++;
	if (!(array = (char**)malloc(sizeof(char*) * i)))
		ft_error(0, venv , "Malloc failed");
	while (commands[trim])
	{
		array[offset] = ft_strdup(commands[trim]);
		offset++;
		trim++;
	}
	array[offset] = NULL;
	return (array);
}

t_env *get_venv(char **venv)
{
	int i;
	t_env *lst;
	t_env *tmp;

	tmp = NULL;
	lst = NULL;
	i = 0;
	while (venv[i])
	{
		if (!(tmp = ft_memalloc(sizeof(t_env))))
			ft_error(0, &lst, "Malloc Failed");
		tmp->content = ft_strdup(venv[i]);
		ft_lst_add_tenv(&lst, tmp);
		i++;
	}
	return (lst);
}

void exec_setenv(char **commands, t_env **venv, int mode)
{
	int i;
	char *tmp;

	i = 0;
	while (commands[i++])
		;
	if (i != 4 && mode == 0)
		ft_putendl("Usage : setenv <Environment variable> <Value>");
	else if (i > 3 || mode == 1)
	{
		if (!find_t_env(venv, commands))
			add_t_env(venv, commands);
		else
		{
			tmp = ft_strjoin((commands[1]), "=");
			ft_modify_tenv(venv, tmp, commands[2]);
			free(tmp);
		}
	}
}

void remove_t_env(t_env **venv)
{
	t_env	*tmp;

	tmp = *venv;
	while (tmp != NULL)
	{
			tmp = *venv;
			if (tmp->next)
				*venv = (*venv)->next;
			else
			{
				ft_strdel(&tmp->content);
				break;
			}
			ft_strdel(&tmp->content);
			free(tmp);
	}
}

void add_t_env(t_env **venv, char **commands)
{
	t_env *tmp;
	char *str_tmp;
	char *str_buf;

	tmp = ft_memalloc(sizeof(t_env));
	str_buf = ft_strjoin(commands[1], "=");
	str_tmp = ft_strjoin(str_buf, commands[2]);
	ft_strdel(&str_buf);
	tmp->content = ft_strdup(str_tmp);
	ft_strdel(&str_tmp);
	ft_lst_add_tenv(venv, tmp);
}

int find_t_env(t_env **venv, char **commands)
{
	t_env *tmp;

	tmp = *venv;

	while (tmp)
	{
		if (find_t_env_array(tmp->content, commands))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int find_t_env_array(char *env, char **search)
{
	int len;

	len = ft_strlen(search[1]);
	if (!ft_strncmp(env, search[1], len))
		if (!ft_strncmp((env + len), "=", 1))
			return (1);
	return (0);
}


int find_t_env_str(char *venv, char *str)
{
	int len;

	len = ft_strlen(str);
	if (!ft_strncmp(venv, str, len))
		if (!ft_strncmp((venv + len), "=", 1))
			return (1);
	return (0);
}

int find_t_env_strr(t_env **venv, char *str)
{
	int i;
	t_env *tmp;

	tmp = *venv;
	i = 0;
	while (tmp)
	{
		if (find_t_env_str(tmp->content, str))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void exec_unsetenv(char **commands, t_env **venv)
{
	int i;

	i = 0;
	while (commands[i++])
		;
	if (i != 3)
		ft_putendl("Usage : unsetenv <Environment variable>");
	else if (find_t_env(venv, commands))
		remove_one_t_env(venv, commands);
	else
		ft_putendl("Environment Variable doesn't exist");
}

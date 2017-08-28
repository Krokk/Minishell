/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 21:21:33 by rfabre            #+#    #+#             */
/*   Updated: 2017/08/28 01:57:27 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_env(t_env *venv)
{
	t_env *tmp;

	tmp = venv;
	while(tmp)
	{
		ft_putendl(tmp->content);
		tmp = tmp->next;
	}
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
		tmp = ft_memalloc(sizeof(t_env));
		tmp->content = ft_strdup(venv[i]);
		ft_lst_add_tenv(&lst, tmp);
		i++;
	}
	return (lst);
}

/*
   remove_t_env ne marche pas sur le premier et dernier maillon

   faire tout paser par access pour les appels de commande

   pour les venv
les : sont les separateur
aller chercher les binaire dans les path et verifier avec acces( si return 0) executer avec fork

bonus SHLVL ; niveau de profondeur des shell incrementer
*/

void exec_setenv(char **commands, t_env *venv)
{
	int i;

	i = 0;
	while (commands[i++])
		;
	if (i != 4)
		ft_putendl("Usage : setenv <Environment variable> <Value>");
	else
	{
		if (!find_t_env(&venv, commands))
			add_t_env(venv, commands);
		else
		{
			remove_t_env(venv, commands);
			add_t_env(venv, commands);
		}
	}
}

void remove_t_env(t_env *venv, char **commands)
{
	t_env	*free_this;
	t_env *tmp;

	tmp = NULL;

	while (venv)
	{
		if (t_env_compare(venv->content, commands))
		{
			free_this = venv;
			if (free_this->next)
				venv = free_this->next;
			if (tmp && venv->next)
				tmp->next = venv;
			free(free_this->content);
			free(free_this);
			if (commands[1])
				break ;
		}
		tmp = venv;
		venv = venv->next;
	}
}

void add_t_env(t_env *venv, char **commands)
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
	ft_lst_add_tenv(&venv, tmp);
}

int find_t_env(t_env **venv, char **commands)
{
	t_env *tmp;

	tmp = *venv;
	while (tmp)
	{
		if (t_env_compare(tmp->content, commands))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int t_env_compare(char *env, char **search)
{
	int len;

	len = ft_strlen(search[1]);
	if (!ft_strncmp(env, search[1], len))
		if (!ft_strncmp((env + len), "=", 1))
			return (1);
	return (0);
}

int find_str_t_env(t_env **venv, char *str)
{
	t_env *tmp;

	tmp = *venv;
	while (tmp)
	{
		if (ft_strequ(str, tmp->content))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}


void exec_unsetenv(char **commands, t_env *venv)
{
	int i;

	i = 0;
	while (commands[i++])
		;
	if (i != 3)
		ft_putendl("Usage : unsetenv <Environment variable>");
	else if (find_t_env(&venv, commands))
		remove_t_env(venv, commands);
	else
		ft_putendl("Environment Variable doesn't exist");
}

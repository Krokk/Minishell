/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 21:10:04 by rfabre            #+#    #+#             */
/*   Updated: 2017/08/28 03:02:23 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_lst_add_tenv(t_env **alst, t_env *new)
{
	t_env		*lst;

	lst = *alst;
	if (lst == NULL)
	{
		*alst = new;
	}
	else
	{
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = new;
	}
}

int ft_modify_tenv(t_env **venv, char *new, char *contents)
{
	t_env *tmp;
	char *buf;
	t_env *tmpp;

	tmp = *venv;
	buf = ft_strjoin(new, contents);
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, new, ft_strlen(new)))
		{
			free(tmp->content);
			tmp->content = ft_strdup(buf);
			ft_strdel(&buf);
			return (1);
		}
		tmp = tmp->next;
	}
	tmpp = ft_memalloc(sizeof(t_env));
	tmpp->content = ft_strdup(buf);
	ft_lst_add_tenv(venv, tmpp);
	ft_strdel(&buf);
	return (0);
}

char *get_venv_value(t_env **venv, char *search)
{
	t_env *tmp;

	tmp = *venv;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, search, ft_strlen(search)))
			return(tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

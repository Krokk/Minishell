/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 21:10:04 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/12 19:02:06 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_lst_add_tenv(t_env **alst, t_env *new)
{
	t_env	*lst;

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

int			ft_modify_tenv(t_env **venv, char *new, char *contents)
{
	t_env	*tmp;
	char	*buf;
	t_env	*tmpp;

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
	if (!(tmpp = ft_memalloc(sizeof(t_env))))
		ft_error(0, venv, "Malloc Failed");
	tmpp->content = ft_strdup(buf);
	ft_lst_add_tenv(venv, tmpp);
	ft_strdel(&buf);
	return (0);
}

char		*get_venv_value(t_env **venv, char *search)
{
	t_env	*tmp;

	tmp = *venv;
	while (tmp)
	{
		if (find_t_env_str(tmp->content, search))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

void		print_pwd(void)
{
	char	tmp[1024 + 1];

	ft_putendl(getcwd(tmp, 1024));
}

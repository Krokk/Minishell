/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 21:21:33 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/09 17:48:30 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**new_array(char **commands, int trim, t_env **venv)
{
	int		offset;
	int		i;
	char	**array;

	i = 0;
	offset = 0;
	while (commands[i])
		i++;
	if (!(array = (char**)malloc(sizeof(char*) * i)))
		ft_error(0, venv, "Malloc failed");
	while (commands[trim])
	{
		array[offset] = ft_strdup(commands[trim]);
		offset++;
		trim++;
	}
	array[offset] = NULL;
	return (array);
}

t_env		*get_venv(char **venv, int ac, char **argv)
{
	int		i;
	t_env	*lst;
	t_env	*tmp;

	(void)ac;
	(void)argv;
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

void		remove_t_env(t_env **venv)
{
	t_env	*tmp;

	while (*venv != NULL)
	{
		tmp = (*venv)->next;
		ft_strdel(&((*venv)->content));
		free(*venv);
		(*venv) = tmp;
	}
}

void		add_t_env(t_env **venv, char **commands)
{
	t_env	*tmp;
	char	*str_tmp;
	char	*str_buf;

	tmp = ft_memalloc(sizeof(t_env));
	str_buf = ft_strjoin(commands[1], "=");
	str_tmp = ft_strjoin(str_buf, commands[2]);
	ft_strdel(&str_buf);
	tmp->content = ft_strdup(str_tmp);
	ft_strdel(&str_tmp);
	ft_lst_add_tenv(venv, tmp);
}

int			find_t_env(t_env **venv, char **commands)
{
	t_env	*tmp;

	tmp = *venv;
	while (tmp)
	{
		if (find_t_env_array(tmp->content, commands))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

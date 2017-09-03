/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 01:49:16 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/03 16:08:43 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**t_env_to_array(t_env **venv)
{
	int		i;
	char	**result;
	t_env	*tmp;
	int		j;

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

void		print_env(t_env *venv)
{
	t_env	*tmp;

	tmp = venv;
	while (tmp != NULL)
	{
		ft_putendl(tmp->content);
		tmp = tmp->next;
	}
}

t_env		*create_new_env(t_env **venv)
{
	t_env	*tmp;
	t_env	*lst;

	lst = NULL;
	tmp = NULL;
	while (*venv)
	{
		if (!(tmp = ft_memalloc(sizeof(t_env))))
			ft_error(0, venv, "Malloc Failed");
		tmp->content = ft_strdup((*venv)->content);
		ft_lst_add_tenv(&lst, tmp);
		venv = &(*venv)->next;
	}
	return (lst);
}

void		exec_env(char **commands, t_env **venv, int *recall)
{
	t_env	*envv;
	int		i;

	i = 0;
	while (commands[i])
		i++;
	if (i == 1)
	{
		if (*venv != NULL)
			print_env(*venv);
	}
	else if (i > 2)
	{
		envv = create_new_env(venv);
		exec_setenv(commands, &envv, 1);
		(*recall)++;
		check_ifbuiltin(commands + 3, &envv, recall);
		if (i == 3)
			print_env(envv);
		remove_t_env(&envv);
	}
}

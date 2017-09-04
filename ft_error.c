/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 03:42:40 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/04 23:47:32 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_error(int erno, t_env **venv, char *msg)
{
	ft_putstr_fd("Minishell : ", 2);
	if (erno == 0)
	{
		ft_putendl_fd(msg, 2);
		remove_t_env(venv);
		exit(1);
	}
	else if (erno == 2)
		ft_putendl_fd(msg, 2);
	else if (erno == 3)
	{
		ft_putstr_fd("no such file or directory : ", 2);
		ft_putendl_fd(msg, 2);
	}
	return (0);
}

void		remove_one_t_env(t_env **venv, char **commands)
{
	t_env	*free_this;

	while (*venv)
	{
		if (find_t_env_array((*venv)->content, commands))
		{
			free_this = *venv;
			*venv = free_this->next;
			free(free_this->content);
			free(free_this);
			break ;
		}
		venv = &(*venv)->next;
	}
}

void		print_prompt(void)
{
	ft_putstr(BLUE);
	ft_putstr("$>> ");
	ft_putstr(DEFAULT);
}

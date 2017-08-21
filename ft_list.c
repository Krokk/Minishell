/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 21:10:04 by rfabre            #+#    #+#             */
/*   Updated: 2017/08/21 23:13:19 by rfabre           ###   ########.fr       */
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
        new->prev = lst;
	}
}

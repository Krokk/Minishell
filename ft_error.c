/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 03:42:40 by rfabre            #+#    #+#             */
/*   Updated: 2017/08/28 05:08:48 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_error(int erno, t_env **venv, char *msg)
{
    ft_putendl_fd("Minishell : ", 2);
    if (erno == 0)
    {
        ft_putendl_fd(msg, 2);
        remove_t_env(venv, NULL);
    }
        exit (1);
}

//
int exit_shell(void)
{
    exit (0);
}

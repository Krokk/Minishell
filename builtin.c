/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 15:55:44 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/03 15:55:51 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_echo(char **commands)
{
	int		i;
	int		do_new_line;

	do_new_line = 1;
	i = 1;
	if (ft_strequ(commands[1], "-n"))
	{
		do_new_line = 0;
		i++;
	}
	while (commands[i])
	{
		if ((do_new_line == 1 && i > 1) || i > 2)
			ft_putstr(" ");
		ft_putstr(commands[i]);
		i++;
	}
	if (do_new_line)
		ft_putstr("\n");
}

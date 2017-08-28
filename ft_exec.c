/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 21:22:31 by rfabre            #+#    #+#             */
/*   Updated: 2017/08/28 01:56:38 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_execcommands(char **commands, char *binary)
{
	pid_t	pid;

	pid = fork();
	while (1)
	{
		if (pid == 0)
		{
			wait(&pid);
			execve(binary, commands, NULL);
			exit(0);
		}
		if (pid > 0)
		{
			wait(0);
			break ;
		}
	}
}

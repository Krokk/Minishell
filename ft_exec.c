/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 21:22:31 by rfabre            #+#    #+#             */
/*   Updated: 2017/08/21 22:27:04 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_execcommands(char **commands, char *binary)
{
	pid_t pid;

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
			break;
		}
	}
}

// void exit_minishell(void)
// {
//     // ft_freearraystr(commands);
//     // ft_strdel(&request);
//     exit(0);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 17:26:28 by rfabre            #+#    #+#             */
/*   Updated: 2017/08/17 17:06:07 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void get_request(char **request)
{
	int		ret;
	char	buf[2];

    *request = ft_strnew(1);
	while ((ret = read(0, &buf, 1)) && !ft_strchr(buf, '\n'))
    {
        buf[ret] = '\0';
        *request = ft_freejoin(*request, buf);
    }
	if (!ret)
		ft_putendl("DEBUG READ");
    if (*(*request))
    {
        ft_putstr(*request);
        ft_putstr("\n");
    }
}

static void ft_execcommands(char **commands)
{
	pid_t pid;

	pid = fork();
	while (1)
	{
		if (pid == 0)
		{
			sleep(1);
			ft_putendl("ok negro je lance la commande");
			execve(commands[0], commands, NULL);
			exit(0);
		}
		if (pid > 0)
		{
			break;
			wait(0);
		}
	}
}

int main(int ac, char **argv, char **venv)
{
    char *request;
    char **commands;

    while (1)
    {
    	get_request(&request);
    	if (ft_strstr(request, "exit"))
        	return (0);
		commands = ft_strsplit(request,' ');
		ft_strdel(&request);
		free(request);
		ft_strtrim(*commands);
		ft_execcommands(commands);
    }
    return (0);
}

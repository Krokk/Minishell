/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 17:26:28 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/01 02:24:13 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void get_request(char **request, t_env **venv)
{
	int		ret;
	char	buf[2];

	ret = 0;
	ft_bzero(buf, 3);
	if (!(*request = ft_memalloc(sizeof(char))))
		ft_error(0, venv, "Malloc failed");
	while ((ret = read(0, &buf, 1)) && ft_strcmp(buf, "\n"))
	{
		buf[ret] = '\0';
		*request = ft_freejoinstr(*request, buf);
	}
	if (ret == -1)
		ft_error(0, venv, "Read Failure");
}



void check_ifbuiltin(char **commands, t_env **venv)
{
	if (commands[0] != NULL)
	{
		if (ft_strequ(commands[0], "echo"))
			exec_echo(commands);
		else if (ft_strequ(commands[0], "cd"))
			exec_cd(commands, venv);
		else if (ft_strequ(commands[0], "setenv"))
			exec_setenv(commands, venv, 0);
		else if (ft_strequ(commands[0], "unsetenv"))
			exec_unsetenv(commands, venv);
		else if (ft_strequ(commands[0], "env"))
			exec_env(commands, venv);
		else if (ft_strequ(commands[0], "pwd"))
			print_pwd();
		else if (ft_strequ(commands[0], "clear"))
			ft_putstr("\033[H\033[J");
		else
			look_for_binary(commands, venv);
	}
}

int main(int ac, char **argv, char **venv)
{
	char *request;
	char **commands;
	t_env *envv;
	char *parsed_commands;

	(void)ac;
	(void)argv;

	envv = get_venv(venv);
	while (1)
	{
		ft_putstr("$> ");
		get_request(&request, &envv);
		commands = ft_strsplit(request,' ');
		free(request);
		parsed_commands = ft_strtrim(*commands);
		free(parsed_commands);
		if (ft_strequ(commands[0], "exit"))
		{
			ft_freearraystr(commands);
			exit (0);
		}
		check_ifbuiltin(commands, &envv);
		ft_freearraystr(commands);
	}
	return (0);
}

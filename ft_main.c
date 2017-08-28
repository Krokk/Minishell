/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 17:26:28 by rfabre            #+#    #+#             */
/*   Updated: 2017/08/28 03:10:26 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void get_request(char **request)
{
	int		ret;
	char	buf[2];

	*request = ft_memalloc(sizeof(char));
	while ((ret = read(0, &buf, 1)) && ft_strcmp(buf, "\n"))
	{
		buf[ret] = '\0';
		*request = ft_freejoinstr(*request, buf);
	}
	if (!ret)
		ft_putendl("DEBUG READ");
}

static void check_ifbuiltin(char **commands, t_env **venv)
{
	if (ft_strequ(commands[0], "echo"))
		exec_echo(commands);
	else if (ft_strequ(commands[0], "cd"))
		exec_cd(commands, venv);
	else if (ft_strequ(commands[0], "setenv"))
		exec_setenv(commands, venv);
	else if (ft_strequ(commands[0], "unsetenv"))
		exec_unsetenv(commands, venv);
	else if (ft_strequ(commands[0], "env"))
		print_env(*venv);
	else if (ft_strequ(commands[0], "pwd"))
		ft_putendl(print_pwd());
	else if (ft_strequ(commands[0], "ls"))
		ft_execcommands(commands, "/bin/ls");
	else if (ft_strequ(commands[0], "clear"))
		ft_putstr("\033[H\033[J");
	else
		ft_putendl("Command not recognized");
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
		get_request(&request);
		if (ft_strequ(request, "exit"))
			exit(0);
		commands = ft_strsplit(request,' ');
		free(request);
		parsed_commands = ft_strtrim(*commands);
		check_ifbuiltin(commands, &envv);
		ft_freearraystr(commands);
		free(parsed_commands);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 17:26:28 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/04 23:48:41 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		get_multiple_request(char *tmp, t_env **multi_cmd, t_env **venv)
{
	char		**array;
	int			i;
	t_env		*tmpp;

	i = 0;
	array = NULL;
	array = ft_strsplit(tmp, ';');
	if (array)
	{
		while (array[i])
		{
			{
				if (!(tmpp = ft_memalloc(sizeof(t_env))))
					ft_error(0, venv, "Malloc Failed");
				tmpp->content = ft_strtrim(array[i]);
				ft_lst_add_tenv(multi_cmd, tmpp);
			}
			i++;
		}
		ft_freearraystr(array);
	}
}

static void		get_request(t_env **venv, t_env **cmd, int *recall)
{
	int			ret;
	char		buf[2];
	char		*tmp;
	char		*request;

	ret = 0;
	print_prompt();
	recall = 0;
	ft_bzero(buf, 3);
	if (!(request = ft_memalloc(sizeof(char))))
		ft_error(0, venv, "Malloc failed");
	while ((ret = read(0, &buf, 1)) && ft_strcmp(buf, "\n"))
	{
		buf[ret] = '\0';
		request = ft_freejoinstr(request, buf);
	}
	if (ret == -1)
		ft_error(0, venv, "Read Failure");
	tmp = ft_strtrim(request);
	get_multiple_request(tmp, cmd, venv);
	if (ret)
	{
		free(tmp);
		free(request);
	}
}

void			check_if_builtin(char **commands, t_env **venv, int *recall)
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
			exec_env(commands, venv, recall);
		else if (ft_strequ(commands[0], "pwd"))
			print_pwd();
		else if (ft_strequ(commands[0], "clear"))
			ft_putstr("\033[H\033[J");
		else
			look_for_binary(commands, venv);
	}
}

static void		check_exit_norme(char **commands, t_env **venv,
		t_env **multi_cmd)
{
	if (ft_strequ(commands[0], "exit"))
	{
		remove_t_env(venv);
		ft_freearraystr(commands);
		remove_t_env(multi_cmd);
		exit(0);
	}
}

int				main(int ac, char **argv, char **venv)
{
	char		**commands;
	t_env		*envv;
	t_env		*multi_cmd;
	int			recall;
	t_env		*tmp;

	multi_cmd = NULL;
	envv = get_venv(venv, ac, argv);
	while (1)
	{
		get_request(&envv, &multi_cmd, &recall);
		tmp = multi_cmd;
		while (tmp)
		{
			commands = ft_strsplit(tmp->content, ' ');
			check_exit_norme(commands, &envv, &multi_cmd);
			check_if_builtin(commands, &envv, &recall);
			ft_freearraystr(commands);
			tmp = tmp->next;
		}
		remove_t_env(&multi_cmd);
	}
	return (0);
}

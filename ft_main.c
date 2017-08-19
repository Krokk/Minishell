/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 17:26:28 by rfabre            #+#    #+#             */
/*   Updated: 2017/08/19 19:05:36 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void get_request(char **request)
{
	int		ret;
	char	buf[2];

    *request = ft_strnew(1);
	while ((ret = read(0, &buf, 1)) && ft_strcmp(buf, "\n"))
    {
        buf[ret] = '\0';
        *request = ft_freejoinstr(*request, buf);
    }
	if (!ret)
		ft_putendl("DEBUG READ");
	/*DEBUG
    if (*(*request))
    {
        ft_putstr(*request);
        ft_putstr("\n");
    }*/
}

static void ft_execcommands(char **commands)
{
	pid_t pid;

	pid = fork();
	while (1)
	{
		if (pid == 0)
		{
			wait(&pid);
			execve(commands[0], commands, NULL);
			exit(0);
		}
		if (pid > 0)
		{
			wait(0);
			break;
		}
	}
}

void execrealcommand(char **commands)
{
	if (ft_strequ(commands[0], "ls"))
		execve("/bin/ls", commands, NULL);
}

static t_list *get_venv(char **venv)
{
	int i;
	t_list *lst;
	t_list *tmp;

	tmp = NULL;
	lst = NULL;
	i = 0;
	while (venv[i])
	{
		tmp = ft_memalloc(sizeof(t_list));
		tmp->content = ft_strdup(venv[i]);
		if (!lst)
			lst = tmp;
		else
			ft_lstaddend(&lst, tmp);
		i++;
	}
	return (lst);
}

static void print_env(t_list *venv)
{
	int i;

	i = 0;
	while(venv)
	{
		ft_putendl((char*)venv->content);
		venv = venv->next;
	}
}

static void check_ifbuiltin(char **commands, t_list *venv)
{
	if (ft_strequ(commands[0], "echo"))
		exec_echo(commands);
	// else if (ft_strequ(commands[0], "cd"))
	// 	exec_cd(commands);
	// else if (ft_strequ(commands[0], "setenv"))
	// 	exec_setenv(commands);
	// else if (ft_strequ(commands[0], "unsetenv"))
	// 	exec_unsetenv(commands);
	else if (ft_strequ(commands[0], "env"))
		print_env(venv);
	else if (ft_strequ(commands[0], "pwd"))
		print_pwd();
	else
		ft_putendl("Command not recognized");
}

void exec_echo(char **commands)
{
	int i;

	i = 1;
	while (commands[i])
	{
		if (i > 1)
			ft_putstr(" ");
		ft_putstr(commands[i]);
		i++;
	}
	ft_putstr("\n");
}
// PATH=/Users/rfabre/.brew/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/munki

void print_pwd(void)
{
	char tmp[1024 + 1];
	char *cwd;

	cwd = getcwd(tmp, 1024);
	ft_putstr(cwd);
	ft_putstr("\n");

}
int main(int ac, char **argv, char **venv)
{
    char *request;
    char **commands;
	t_list *envv;
	int i;

	envv = get_venv(venv);
	while (1)
    {
		ft_putstr("$> ");
    	get_request(&request);
    	if (ft_strequ(request, "exit"))
        	return (0);
		commands = ft_strsplit(request,' ');
		ft_strdel(&request);
		free(request);
		ft_strtrim(*commands);
		check_ifbuiltin(commands, envv);
			// ft_execcommands(commands);
		ft_freearraystr(commands);
    }
    return (0);
}

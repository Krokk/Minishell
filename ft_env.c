/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 21:21:33 by rfabre            #+#    #+#             */
/*   Updated: 2017/08/22 01:42:59 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_env(t_env *venv)
{
	t_env *tmp;

	tmp = venv;
	while(tmp)
	{
		ft_putendl(tmp->content);
		tmp = tmp->next;
	}
	free(tmp);
}

t_env *get_venv(char **venv)
{
	int i;
	t_env *lst;
	t_env *tmp;

	tmp = NULL;
	lst = NULL;
	i = 0;
	while (venv[i])
	{
		tmp = ft_memalloc(sizeof(t_env));
		tmp->content = ft_strdup(venv[i]);
		ft_lst_add_tenv(&lst, tmp);
		i++;
	}
	return (lst);
}

void exec_setenv(char **commands, t_env *venv)
{
    int i;
    char	buf[2];
    int		ret;

    i = 0;
    while (commands[i++])
        ;
    if (i != 4)
        ft_putendl("Usage : setenv <Environment variable> <Value>");
    else
    {
        if (!find_t_env(venv, commands))
            add_t_env(venv, commands);
        else
            {
                ft_putendl("Environment value already exist would you like to override ?");
                ret = read(0, &buf, 1) && ft_strcmp(buf, "\n");
                buf[ret] = '\0';
                if ((ft_strcmp(buf,"y")) || ft_strncmp(buf, "Y", 2))
                {
                    remove_t_env(venv, commands);
                    add_t_env(venv, commands);
                }
                else
                    ;
            }
    }
}

t_env *remove_t_env(t_env *venv, char **commands)
{
    t_env *tmp;
    t_env *previous;

    previous = venv;
    if (!ft_strcmp(commands[1], venv->content))
    {
        venv = venv->next;
        free(previous);
    }
    else
    {
        tmp = previous->next;
        while (tmp)
        {
            if (!ft_strcmp(commands[1], tmp->content))
            {
                previous->next = tmp->next;
                free(tmp);
                break;
            }
            previous = tmp;
            tmp = tmp->next;
        }
    }
}

void add_t_env(t_env *venv, char **commands)
{
    t_env *tmp;
    char *str_tmp;
    char *str_buf;

    tmp = ft_memalloc(sizeof(t_env));
    str_buf = ft_strjoin(commands[1], "=");
    str_tmp = ft_strjoin(str_buf, commands[2]);
    ft_strdel(&str_buf);
    tmp->content = ft_strdup(str_tmp);
    ft_strdel(&str_tmp);
    ft_lst_add_tenv(&venv, tmp);
}

int find_t_env(t_env *venv, char **commands)
{
    t_env *tmp;

    tmp = venv;
    while (tmp)
    {
        if (ft_strncmp(commands[1], tmp->content, ft_strlen(commands[1])) == 0)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

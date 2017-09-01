/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 01:49:16 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/01 02:56:13 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_env(t_env *venv)
{
	t_env *tmp;

	if (venv)
		tmp = venv;
	while(tmp)
	{
		ft_putendl(tmp->content);
		tmp = tmp->next;
	}
}

t_env **create_new_env(t_env **venv)
{
    t_env *tmp;
    t_env *lst;

    lst = NULL;
    tmp = NULL;
    while (*venv)
    {
        if (!(tmp = ft_memalloc(sizeof(t_env))))
            ft_error(0, venv, "Malloc Failed");
        tmp->content = ft_strdup((*venv)->content);
        ft_lst_add_tenv(&lst, tmp);
        venv = &(*venv)->next;
    }
    return (lst);
}

void exec_env(char **commands, t_env **venv)
{
    t_env *envv;
    int i;

    i = 0;
    while (commands[i])
        i++;
    if (i == 1)
        print_env(*venv);
    else if (i == 4)
    {
        envv = create_new_env(venv);
        exec_setenv(commands, &envv, 1);
        check_ifbuiltin(commands + 3, &envv);
        remove_t_env(1, commands, envv);
    }
    else
        ft_putendl("Usage : env> or <env> <environment variable> <value> <command>");
}

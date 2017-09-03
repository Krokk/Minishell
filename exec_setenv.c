/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 16:02:36 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/03 16:04:28 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_setenv(char **commands, t_env **venv, int mode)
{
	int		i;
	char	*tmp;

	i = 0;
	while (commands[i++])
		;
	if (i != 4 && mode == 0)
		ft_putendl("Usage : setenv <Environment variable> <Value>");
	else if (i > 3 || mode == 1)
	{
		if (!find_t_env(venv, commands))
			add_t_env(venv, commands);
		else
		{
			tmp = ft_strjoin((commands[1]), "=");
			ft_modify_tenv(venv, tmp, commands[2]);
			free(tmp);
		}
	}
}

int			find_t_env_array(char *env, char **search)
{
	int		len;

	len = ft_strlen(search[1]);
	if (!ft_strncmp(env, search[1], len))
		if (!ft_strncmp((env + len), "=", 1))
			return (1);
	return (0);
}

int			find_t_env_str(char *venv, char *str)
{
	int		len;

	len = ft_strlen(str);
	if (!ft_strncmp(venv, str, len))
		if (!ft_strncmp((venv + len), "=", 1))
			return (1);
	return (0);
}

int			find_t_env_strr(t_env **venv, char *str)
{
	t_env	*tmp;

	tmp = *venv;
	while (tmp)
	{
		if (find_t_env_str(tmp->content, str))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void		exec_unsetenv(char **commands, t_env **venv)
{
	int		i;

	i = 0;
	while (commands[i++])
		;
	if (i != 3)
		ft_putendl("Usage : unsetenv <Environment variable>");
	else if (find_t_env(venv, commands))
		remove_one_t_env(venv, commands);
	else
		ft_putendl("Environment Variable doesn't exist");
}

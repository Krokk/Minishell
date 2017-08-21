/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 19:41:19 by rfabre            #+#    #+#             */
/*   Updated: 2017/08/21 21:19:54 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_pwd(void)
{
	char tmp[1024 + 1];
	char *cwd;

	cwd = getcwd(tmp, 1024);
	ft_putstr(cwd);
	ft_putstr("\n");

}

void exec_echo(char **commands)
{
	int i;
	int do_new_line;

	do_new_line = 1;
	i = 1;
	/*if TODO: parser pour verifier si il y a des " "
	affichier le contenu entre " " tel quel.
    gerer aussi : on peut utiliser echo texte " puis encore du text"
	*/
	if (ft_strequ(commands[1], "-n"))
	{
		do_new_line = 0;
		i++;
	}
	while (commands[i])
	{
		if ((do_new_line == 1 && i > 1) || i > 2)
			ft_putstr(" ");
		ft_putstr(commands[i]);
		i++;
	}
	if (do_new_line)
		ft_putstr("\n");
}

void exec_cd(char **commands)
{
		int i;

		i = 0;
		while (commands[i++])
			;
		if (i != 3)
			ft_putendl("Usage : cd <directory>");
		else
		{
			if (chdir(commands[1]) == 0)
			{
				ft_putstr("directory changed to : ");
				ft_putendl(commands[1]);
			}
			else
				perror(commands[1]);
		}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 15:33:22 by rfabre            #+#    #+#             */
/*   Updated: 2017/08/22 00:17:23 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include <unistd.h>
# include <stdio.h>

typedef	struct		s_env
{
	char			*content;
	struct s_env	*next;
    struct s_env    *prev;
}					t_env;


void execrealcommand(char **commands);
void print_pwd(void);
void exec_pwd(char **commands);
void exec_echo(char **commands);
void exec_cd(char **commands);
void			ft_lst_add_tenv(t_env **alst, t_env *new);
void print_env(t_env *venv);
t_env *get_venv(char **venv);
// void ft_execcommands(char **commands, char *binary);
void exit_minishell(char **commands, char *request);
void ft_execcommands(char **commands, char *binary);
void exec_setenv(char **commands, t_env *venv);
void add_t_env(t_env *venv, char **commands);
int find_t_env(t_env *venv, char **commands);
t_env *remove_t_env(t_env *venv, char **commands);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 15:33:22 by rfabre            #+#    #+#             */
/*   Updated: 2017/08/28 03:10:22 by rfabre           ###   ########.fr       */
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

// int parse_cd(char **cmd, t_env *venv);
char *get_venv_value(t_env **venv, char *search);
int ft_modify_tenv(t_env **venv, char *new, char *contents);
void execrealcommand(char **commands);
char *print_pwd(void);
void exec_pwd(char **commands);
void exec_echo(char **commands);
void exec_cd(char **commands, t_env **venv);
void			ft_lst_add_tenv(t_env **alst, t_env *new);
void print_env(t_env *venv);
t_env *get_venv(char **venv);
// void ft_execcommands(char **commands, char *binary);
void exit_minishell(char **commands, char *request);
void ft_execcommands(char **commands, char *binary);
void exec_setenv(char **commands, t_env **venv);
void add_t_env(t_env **venv, char **commands);
int find_t_env(t_env **venv, char **commands);
void remove_t_env(t_env **venv, char **commands);
void exec_unsetenv(char **commands, t_env **venv);
int find_str_t_env(t_env **venv, char *str);
int t_env_compare(char *env, char **search);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 15:33:22 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/09 15:43:56 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/libft.h"
# include <unistd.h>
# include <sys/stat.h>
# include <stdio.h>
# include <sys/types.h>
# include <dirent.h>

typedef	struct		s_env
{
	char			*content;
	struct s_env	*next;
}					t_env;

int					ft_access_chk(char *path, t_env **venv);
int					found_binary(char **path, char **commands, t_env **venv,
	int ret);
void				check_if_builtin(char **commands, t_env **venv,
	int *recall);
int					parse_target(char **commands, t_env **venv);
void				look_for_binary(char **commands, t_env **venv);
t_env				*ft_copy_t_env(t_env **venv);
char				**new_array(char **commands, int trim, t_env **venv);
int					check_cd(char **commands, t_env **venv, int size);
char				*get_venv_value(t_env **venv, char *search);
int					ft_modify_tenv(t_env **venv, char *new, char *contents);
void				print_pwd(void);
void				exec_pwd(char **commands);
void				exec_echo(char **commands);
void				exec_cd(char **commands, t_env **venv);
void				ft_lst_add_tenv(t_env **alst, t_env *new);
void				print_env(t_env *venv);
t_env				*get_venv(char **venv, int ac, char **argv);
void				print_prompt(void);
void				do_cd(char *path, t_env **venv);
char				*parse_cd(int ret, t_env **venv, char **commands);
void				ft_execcommands(char *path, char **commands, t_env **venv);
void				exec_setenv(char **commands, t_env **venv, int mode);
void				add_t_env(t_env **venv, char **commands);
int					find_t_env(t_env **venv, char **commands);
void				remove_t_env(t_env **venv);
void				remove_one_t_env(t_env **venv, char **commands);
void				exec_unsetenv(char **commands, t_env **venv);
int					find_t_env_str(char *venv, char *str);
int					find_t_env_strr(t_env **venv, char *str);
int					find_t_env_array(char *env, char **search);
int					ft_error(int erno, t_env **venv, char *msg);
void				exit_shell(char **cmd, t_env **env);
char				**t_env_to_array(t_env **venv);
void				exec_env(char **commands, t_env **venv, int *recall);
#endif

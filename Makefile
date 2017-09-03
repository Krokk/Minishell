# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/21 21:23:59 by rfabre            #+#    #+#              #
#    Updated: 2017/09/03 18:16:42 by rfabre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re
NAME = minishell
CFLAGS += -Wall -Wextra -Werror
SRC = ft_main.c\
	  builtin.c\
	  exec_cd.c\
	  exec_env.c\
	  ft_error.c\
	  list.c\
	  array.c\
	  exec_setenv.c\
	  exec_command.c

LIB = ./libft/libft.a
CC = @cc
OBJ = $(SRC:.c=.o)

# COLOR
C_GOOD = "\033[32m"
C_DURING = "\033[36m"
C_FINI = "\033[0m"

# MESSAGE
SUCCESS = $(C_GOOD)"\t'MAKE' ->\t\033[1;34m$(NAME): \033[0m  \tLibrary compilation completed successfully"$(C_FINI)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@echo $(C_GOOD)"\t'MAKE' ->\t\033[1;34m$(NAME): \033[0m  \tLibrary compilation in progress..."$(C_FINI)
	$(CC) $(OBJ) $(LIB) -o $(NAME)
	@echo $(SUCCESS)

clean:
	@make clean -C libft/
	@/bin/rm -f $(OBJ)
	@echo $(C_GOOD)".o FILES DELETED" $(C_FINI)

fclean: clean
	@make fclean -C libft/
	@/bin/rm -f $(NAME)
	@echo $(C_GOOD)"EXECUTABLE FILE DELETED" $(C_FINI)

re: fclean all

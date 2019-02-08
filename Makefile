# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccodiga <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/15 16:17:22 by ccodiga           #+#    #+#              #
#    Updated: 2019/01/15 14:12:19 by ccodiga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	./main.c \
		./keys_environ.c \
		./ft_builtins.c \
		./env_setenv_unsetenv.c \
		./parse_input.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

LIB = ./libft/libft.a

$(NAME): $(LIB)
	@gcc $(FLAGS) $(SRC) $(LIB) -o $(NAME);
	@echo compiling minishell

all: $(NAME)

$(LIB):
	@make -C libft/

clean:
	@rm -rf $(OBJ) libft/$(OBJ)
	@echo deleting binary files

fclean: clean
	@rm -rf $(NAME) libft/libft.a
	@rm -rf libft/*.o
	@echo deleting libft.a and minishell

re: fclean all

.PHONY : all, re, clean, fclean

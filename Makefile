# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccodiga <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/15 16:17:22 by ccodiga           #+#    #+#              #
#    Updated: 2019/02/14 15:28:35 by ccodiga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	./main.c \
		./openquote.c \
		./parse_input.c \
		./expansions.c \
		./cd.c \
		./echo.c \
		./exit.c \
		./env_setenv_unsetenv.c \
		./pipe.c \
		./redirection.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

MINISHELL_SRCS = $(addprefix srcs/,$(SRC))

LIB = ./libft/libft.a

INC= -I./includes

$(NAME): $(LIB)
	@gcc $(FLAGS) $(INC) $(MINISHELL_SRCS) $(LIB) -o $(NAME);
	@echo compiling minishell

all: $(NAME)

$(LIB):
	@make -C libft/

clean:
	@rm -rf $(OBJ) libft/$(OBJ)
	@echo deleting binary files

fclean: clean
	@rm -rf $(NAME) libft/libft.a
	@make fclean -C libft
	@echo deleting libft.a and minishell

re: fclean all

.PHONY : all, re, clean, fclean

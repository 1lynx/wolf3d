# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchampda <cchampda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/27 11:23:48 by nrandria          #+#    #+#              #
#    Updated: 2016/06/10 11:39:03 by cchampda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, fclean, clean, re

NAME = libft/libft.a

SRC =	srcs/main.c		\

EXE = fractol

GCC = gcc -Wall -Wextra -Werror -framework OpenGL -framework SDL2 -O3 -Ofast


all: $(NAME)

$(NAME):
		@echo "\033[33mLibrary's compilation\033[0m"
		@make -C libft/
		@echo "\033[33mProject's compilation\033[0m"
		@$(GCC) $(SRC) $(NAME)
		@echo "\033[33mAll compilation done\033[0m" "\033[32m [ok] \033[32m"

clean:
				@echo "\033[33mLibrary's cleaning\033[0m"
				@make -C libft/ clean

fclean: clean
		@rm -rf $(EXE)
		@rm -rf $(NAME)
		@make -C libft/ fclean

re: fclean all

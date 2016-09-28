# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchampda <cchampda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/06 19:57:23 by cchampda          #+#    #+#              #
#    Updated: 2016/09/28 16:18:24 by cchampda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, fclean, clean, re

NAME = wolf

CC = clang

LIB = libft/libft.a

FLAG = -Wall -Wextra -Werror

LIBGRPH = -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2

INC = header/wolf.h

OBJ =  srcs/main.o	\
		srcs/engine.o \
		srcs/tool.o \
		srcs/key.o \
		srcs/calcul.o \
		srcs/openfile.o \

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
		@$(CC) $(FLAG) $(OBJ) $(LIB) -o $(NAME) $(LIBGRPH)

$(LIB):
		@echo "\033[33mLibft compilation\033[0m"
		@make -C libft/
		@echo "\033[33mProject compilation\033[0m"
		@echo "\033[32mCompilation SUCCESS\033[0m"

%.o : %.c $(INC)
		@$(CC) -c $(FLAG) $< -o $@

clean:
		@echo "\033[33m.o's cleaning\033[0m"
		@rm -f $(OBJ)

fclean: clean
		@make fclean -C libft/
		@rm -rf $(NAME)

re: fclean all

norme:
		@echo "\033[33mChecking Norm of SRCS\033[0m"
		@norminette srcs/*.c
		@echo
		@echo "\033[33mChecking Norm of HEADER\033[0m"
		@norminette $(INC)

gpush:
		@echo "\033[33m.Adding Modified Files on Git\033[0m"
		@git add *
		@echo "\033[33m.Commiting Files on Git\033[0m"
		@git commit -m "`date +%d/%m-%Hh%M`"
		@echo "\033[33m.Pushing Files on Git\033[0m"
		@git push

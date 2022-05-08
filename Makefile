# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 18:22:31 by mrantil           #+#    #+#              #
#    Updated: 2022/05/08 11:58:36 by mrantil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_ls

CC			=	gcc
CFLAGS 		= 	-Wall -Wextra -Werror -g -fsanitize=address -O3 $(INC)

#TERMCAPS 	= 	-ltermcap

DIR_MAIN 	= 	./
_SRC	 	= 	srcs/main.c

OBJ_FILES 	= 	$(DIR_OBJS)*.o
DIR_OBJS 	= 	objs/
OBJS 		= 	$(patsubst %,$(DIR_MAIN)/%,$(OBJ_FILES))

DIR_INC 	=	includes
_INC 		= 	ft_ls.h
INC 		= 	$(patsubst %,$(DIR_INC)/%,$(_INC))

all: libft $(NAME)

$(NAME): $(DIR_OBJS) libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) libft.a

$(DIR_OBJS):
	make -C libft
	cp libft/libft.a .
	mkdir -p $(DIR_OBJS)
	$(CC) $(CFLAGS) -c $(_SRC)
	mv *.o $(DIR_OBJS)

libft:
	make -C libft
	cp libft/libft.a .

clean:
	@make -C libft clean
	@rm -f $(OBJS)
	@rm -f libft.a
	@echo ft_ls object files removed.

fclean:
	@make -C libft fclean
	@rm -f $(NAME)
	@rm -rf $(DIR_OBJS)
	@rm libft.a
	@echo ft_ls binary removed.

re: fclean all

.PHONY: all libft clean fclean re

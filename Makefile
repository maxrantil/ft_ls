# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 18:22:31 by mrantil           #+#    #+#              #
#    Updated: 2022/05/08 14:04:24 by mrantil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_ls

CC			=	gcc
CFLAGS 		= 	-Wall -Wextra -Werror -g -fsanitize=address -O3
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

$(NAME): libft

	$(CC) $(CFLAGS) -o $(NAME) $(_SRC) libft.a

#$(DIR_OBJS):
#	make -C libft
#	cp libft/libft.a .
#	mkdir -p $(DIR_OBJS)
#	$(CC) $(CFLAGS) $(_SRC) $(INC) libft.a
#	mv *.o $(DIR_OBJS)

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

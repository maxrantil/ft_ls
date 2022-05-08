# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 18:22:31 by mrantil           #+#    #+#              #
#    Updated: 2022/05/08 23:06:48 by mrantil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_ls

CC			=	gcc
CFLAGS 		= 	-Wall -Wextra -Werror -g -fsanitize=address -O3
#TERMCAPS 	= 	-ltermcap

SOURCES = srcs
OBJECTS = objs
INCLUDES = includes
LIBRARIES = libraries

FILES 		= 	\
				main

DIR_MAIN 	= 	srcs/
_SRC	 	= 	main.c
SRC 		= 	$(patsubst %,$(DIR_MAIN)%,$(_SRC))

DIR_OBJS 	= 	objs/
OBJS 		= 	$(patsubst %,$(DIR_MAIN)%,$(DIR_OBJS))

DIR_INC 	=	includes/
_INC 		= 	ft_ls.h
INC 		= 	$(patsubst %,$(DIR_INC)%,$(_INC))

C_PATHS = $(addsuffix .c, $(addprefix $(SOURCES)/, $(FILES)))
O_PATHS = $(addsuffix .o, $(addprefix $(OBJECTS)/, $(FILES)))


all: libft $(NAME)

$(NAME): $(DIR_OBJS) $(O_PATHS) libft
	$(CC) $(CFLAGS) -o $@ $(O_PATHS) libft.a

$(DIR_OBJS):
	make -C libft
	cp libft/libft.a .
	mkdir -p $(DIR_OBJS)

$(O_PATHS): $(OBJECTS)/%.o:$(SOURCES)/%.c $(INC) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

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

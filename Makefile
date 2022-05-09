# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 18:22:31 by mrantil           #+#    #+#              #
#    Updated: 2022/05/09 10:01:27 by mrantil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_ls

CC			=	gcc
CFLAGS 		= 	-Wall -Wextra -Werror -g -fsanitize=address -O3
#TERMCAPS 	= 	-ltermcap

SOURCES = sources
OBJECTS = objects
INCLUDES = includes
LIBRARIES = libraries

FILES 		= 	\
				main

DIR_INC 	=	includes/
_INC 		= 	ft_ls.h
INC 		= 	$(patsubst %,$(DIR_INC)%,$(_INC))

C_PATHS = $(addsuffix .c, $(addprefix $(SOURCES)/, $(FILES)))
O_PATHS = $(addsuffix .o, $(addprefix $(OBJECTS)/, $(FILES)))


all: libft $(NAME)

$(NAME): $(OBJECTS) $(O_PATHS) libft
	$(CC) $(CFLAGS) -o $@ $(O_PATHS) libft.a

$(OBJECTS):
	make -C libft
	cp $(LIBRARIES)/libft.a .
	mkdir -p $(OBJECTS)

$(O_PATHS): $(OBJECTS)/%.o:$(SOURCES)/%.c $(INC) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

libft:
	make -C $(LIBRARIES)
	cp $(LIBRARIES)/libft.a .

clean:
	@make -C libft clean
	@rm -f $(O_PATHS)
	@rm -f libft.a
	@echo ft_ls object files removed.

fclean:
	@make -C libft fclean
	@rm -f $(NAME)
	@rm -rf $(OBJECTS)
	@rm libft.a
	@echo ft_ls binary removed.

re: fclean all

.PHONY: all libft clean fclean re

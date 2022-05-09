# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 18:22:31 by mrantil           #+#    #+#              #
#    Updated: 2022/05/09 16:14:57 by mrantil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_ls
CC			=	gcc
CFLAGS 		= 	-Wall -Wextra -Werror -O3
LEAK_CHECK	=	-g -fsanitize=address

#TERMCAPS 	= 	-ltermcap

SOURCES 	= 	sources
OBJECTS 	= 	objects
INCLUDES	= 	includes
LIBRARIES 	= 	libraries

H_FILES 	= 	ft_ls

FILES 		= 	\
				main

H_PATHS 	= 	$(addsuffix .h, $(addprefix $(INCLUDES)/, $(H_FILES)))
C_PATHS 	= 	$(addsuffix .c, $(addprefix $(SOURCES)/, $(FILES)))
O_PATHS 	= 	$(addsuffix .o, $(addprefix $(OBJECTS)/, $(FILES)))

LIBS		= 	libftprintf.a

all: libft $(NAME)

$(NAME): $(OBJECTS) $(O_PATHS) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $(O_PATHS) $(LIBS) $(LEAK_CHECK)

$(OBJECTS): 
	make -C $(LIBRARIES)
	mkdir -p $(OBJECTS)

$(O_PATHS): $(OBJECTS)/%.o:$(SOURCES)/%.c $(H_PATHS) Makefile
	$(CC) $(CFLAGS) -c $< -o $@ $(LEAK_CHECK)

libft:
	@make -C $(LIBRARIES)
	@cp $(LIBRARIES)/$(LIBS) .

clean:
	@make -C $(LIBRARIES) clean
	@rm -f $(O_PATHS)
	@rm -f $(LIBS)
	@echo ft_ls object files removed.

fclean:
	@make -C $(LIBRARIES) fclean
	@rm -f $(NAME)
	@rm -rf $(OBJECTS)
	@rm -f $(LIBS)
	@echo ft_ls binary removed.

re: fclean all

.PHONY: all libft clean fclean re

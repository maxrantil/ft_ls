# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 18:22:31 by mrantil           #+#    #+#              #
#    Updated: 2022/05/04 22:16:24 by mrantil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_ls

CC			=	gcc
CFLAGS 		= 	-Wall -Wextra -Werror -g -fsanitize=address -O3 -I$(INC) -Ilibft/$(DIR_INC)/

#TERMCAPS 	= 	-ltermcap

DIR_MAIN 	= 	./
_SRC	 	= 	main.c
#SRC_MAIN 	= 	$(addprefix $(DIR_MAIN), $(_SRC))

#SRC 		= 	$(SRC_MAIN)
#_SRC 		= 	$(_SRC_MAIN)

OBJ_FILES 	= 	$(_SRC:.c=.o)
DIR_OBJS 	= 	objs/
#OBJS 		= 	$(patsubst %, $(DIR_OBJS)%, $(_SRC:.c=.o))
OBJS 		= 	$(patsubst %,$(DIR_MAIN)/%,$(OBJ_FILES))
#OBJS 		= 	$(patsubst %,$(DIR_OBJS)/%,$(OBJ_FILES))

DIR_INC 	=	includes
_INC 		= 	ft_ls.h
INC 		= 	$(patsubst %,$(DIR_INC)/%,$(_INC))

all: libft $(NAME) 

libft:
	make -C libft
	cp libft/libft.a .

$(DIR_OBJS):
		mkdir -p $(DIR_OBJS)

$(DIR_OBJS)%.o: $(_SRC)%.c
		$(CC) $(CFLAGS) -o $< -c $@ $(INC)

#$(DIR_OBJS)/%.o: $(_SRC)/%.c 
#    	$(CC) $(CFLAGS) -c $(INC) -o $@ $<  

#$(DIR_OBJS)/%.o: %.c $(INC)
#	$(CC) $(CFLAGS) -c -o $@ $< 

$(NAME): $(DIR_OBJS) $(OBJS) libft
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES)
#libft.a

clean:
	@make -C libft clean
	@rm -f $(OBJS)
	@rm -f libft.a
	@echo ft_ls object files removed.

fclean:
	@make -C libft fclean
	@rm -f $(NAME)
	@rm -rf $(DIR_OBJS)
	@echo ft_ls binary removed.

re: fclean all

.PHONY: all libft clean fclean re

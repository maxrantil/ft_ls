# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 18:22:31 by mrantil           #+#    #+#              #
#    Updated: 2022/07/17 12:53:03 by mrantil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLORS
SHELL := /bin/bash
GREEN = \033[32m
GREEN_BACKGROUND = \033[42m
WHITE_BACKGROUND = \033[47m
VIOLET_BACKGROUND = \033[0;45m
YELLOW_BACKGROUND = \033[0;43m
WHITE = \033[37m
YELLOW = \033[33m
BLACK = \033[30m
VIOLET = \033[35m
RESET = \033[0m
RED = \033[31m
CYAN = \033[36m
BOLD = \033[1m

#PRINTING TOOLS
ERASE_LINE = \033[K
UP = A
DOWN = B
RIGHT = C
LEFT = D
MOVE = \033[

#FORBID KEYBOARD INTERACT
$(shell stty -echo)

MAKEFLAGS	+= --no-print-directory

NAME		=	ft_ls
CC			=	gcc
CFLAGS 		= 	-Wall -Wextra -Werror
CFLAGS		+=	-O3 -flto -Wunreachable-code -Wtype-limits
#-Wpedantic(cant use 0b for defining my bits)
LEAK_CHECK	=	-g
LEAK_CHECK	+=	-fsanitize=address

SOURCES 	= 	srcs
OBJECTS 	= 	objs
INCLUDES	= 	includes
LIBRARIES 	= 	libft

SOURCE_COUNT = $(words $(FILES))

H_FILES 	= 	ft_ls

FILES 		= 	flag_l \
				flag_null \
				flag_recurse \
				main \
				print_file_props \
				tools_print \
				tools_vec \
				tools \
				work_data 

H_PATHS 	= 	$(addsuffix .h, $(addprefix $(INCLUDES)/, $(H_FILES)))
C_PATHS 	= 	$(addsuffix .c, $(addprefix $(SOURCES)/, $(FILES)))
O_PATHS 	= 	$(addsuffix .o, $(addprefix $(OBJECTS)/, $(FILES)))

LIBS		= 	libft.a

HEADERS		=	-I$(INCLUDES)/ -Ilibft/includes/

ASSERT_OBJECT = && printf "$(ERASE_LINE)" && printf "$@ $(GREEN)$(BOLD) ✔$(RESET)" || printf "$@ $(RED)$(BOLD)✘$(RESET)\n"

all: libft $(NAME)

$(NAME): $(OBJECTS) $(O_PATHS)
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ $(O_PATHS) $(LIBS) $(LEAK_CHECK)
	@printf "Compiled $(BOLD)$(GREEN)$(NAME)$(RESET)!\n\n"

$(OBJECTS):
	@make -C $(LIBRARIES)
	@mkdir -p $(OBJECTS)
	@printf "$(GREEN)_________________________________________________________________\n$(RESET)"
	@printf "$(NAME): $(GREEN)$(OBJECTS) directory was created.$(RESET)\n\n\n"

$(O_PATHS): $(OBJECTS)/%.o:$(SOURCES)/%.c $(H_PATHS) Makefile
	@printf "$(MOVE)2$(UP)"
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ $(LEAK_CHECK) $(ASSERT_OBJECT)
	@make pbar

libft:
	@make -C $(LIBRARIES)
	@cp $(LIBRARIES)/$(LIBS) .

clean:
	@make -C $(LIBRARIES) clean
	@rm -rf $(OBJECTS)
	@printf "$(NAME):		$(RED)$(OBJECTS) was deleted$(RESET)\n"

fclean: clean
	@make -C $(LIBRARIES) fclean
	@rm -f $(LIBS)
	@rm -f $(NAME)
	@printf "$(NAME):		$(RED)binary was deleted$(RESET)\n"

re: fclean all

pbar:
	$(eval LOADED_COUNT = $(words $(wildcard $(OBJECTS)/*.o)))
	@printf "\r$(MOVE)76$(RIGHT)Files compiled [$(BOLD)$(GREEN)$(LOADED_COUNT)$(RESET) / $(BOLD)$(GREEN)$(SOURCE_COUNT)$(RESET)]\n"
	@for ((i = 1; i <= $(LOADED_COUNT) * 100 / $(SOURCE_COUNT); i++)); do\
		printf "$(GREEN_BACKGROUND) $(RESET)" ;\
	done ;
	@for ((i = 1; i <= 100 - ($(LOADED_COUNT) * 100 / $(SOURCE_COUNT)); i++)); do\
		printf "$(WHITE_BACKGROUND) $(RESET)" ;\
	done ;
	@printf "$(GREEN_BACKGROUND)$(BOLD)$(WHITE)$(MOVE)55$(LEFT)[$$(($(LOADED_COUNT) * 100 / $(SOURCE_COUNT))).$$(($(LOADED_COUNT) * 1000 / $(SOURCE_COUNT) % 10))%%]$(MOVE)54$(RIGHT)$(RESET)\n"


.PHONY: all libft clean fclean re

#ALLOW KEYBOARD INTERACT
$(shell stty echo)

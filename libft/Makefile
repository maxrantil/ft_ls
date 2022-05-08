# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/04 20:09:11 by mrantil           #+#    #+#              #
#    Updated: 2022/05/08 12:05:40 by mrantil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

CC			=	gcc
CFLAGS		=	-Wall -Wextra -g -O3 -I$(INC_DIR)

#TERMCAPS	=	-ltermcap

_SRC_LIBFT =    ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
				ft_itoa.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c \
				ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c \
				ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c \
				ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c \
				ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c \
				ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c \
				ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c ft_lstnew.c ft_lstdelone.c \
				ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_intlen.c ft_lstcount.c ft_lstaddend.c \
				ft_lstputstr.c ft_isspace.c ft_strcdup.c ft_strclen.c ft_strupdate.c ft_imax.c ft_imin.c \
				get_next_line.c

_SRC_PRINTF = 	ft_printf.c print_int_address.c print_c_str.c print_uint_binary.c \
				print_null_float_oct.c print_hex_astrix_procent.c float_work.c flags_plus_minus_hash_null.c \
				flags_proc_zero_space.c width_and_precision.c tools_write_flags.c tools_itoa_b_getit_nullprint.c \
				colors.c

DIR_LIBFT	=	libft/
#SRC_LIBFT	=	$(addprefix $(DIR_LIBFT), $(_SRC_LIBFT))

DIR_PRINTF	=	ft_printf/
#SRC_PRINTF	=	$(addprefix $(DIR_PRINTF), $(_SRC_PRINTF))

#SRC			=	$(SRC_LIBFT) $(SRC_PRINTF)
_SRC		=	$(_SRC_LIBFT) $(_SRC_PRINTF)

OBJ_FILES	=	$(_SRC:.c=.o)

DIR_OBJS	=	objs/
OBJS		=	$(patsubst %, $(DIR_OBJS)%, $(_SRC:.c=.o))

INC_DIR		=	includes/
_INC		= 	libft.h ft_printf.h get_next_line.h
INC			=	$(addprefix $(INC_DIR), $(_INC))


all: $(NAME)

$(NAME): $(DIR_OBJS) $(OBJS)
	ar rc $(NAME) $(OBJS) $(INC)
	ranlib $(NAME)

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

$(DIR_OBJS)%.o: $(DIR_LIBFT)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_PRINTF)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJS)
	@echo libft object files removed.

fclean:
	@rm -f $(NAME)
	@rm -rf $(DIR_OBJS)
	@echo libft.a removed. Object folder removed.

re: fclean all

.PHONY: all clean fclean re

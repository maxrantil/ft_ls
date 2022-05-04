NAME = ft_ls
FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
#HEADER_PATH = libft.h
LIBS = includes/libftprintf.a
C_FILES = main.c
O_FILES = $(C_FILES:.c=.o)

all: $(NAME)

$(NAME):
	@echo "This is ft_ls!"
	@echo ""
	@echo "    ****   **          **       "
	@echo "  /**/   /**         /**        "
	@echo " ****** ******       /**  ******"
	@echo "///**/ ///**/        /** **//// "
	@echo "  /**    /**         /**//***** "
	@echo "  /**    /**         /** /////**"
	@echo "  /**    //**  ***** *** ****** "
	@echo "  //      //  ///// /// //////  "
	@echo ""
	@gcc $(FLAGS) $(C_FILES) -o $(NAME) -I $(LIBS)
#$(HEADER_PATH)
	@echo "$(NAME) created"
	
clean:
	@echo "Cleaning object files..."
	@rm -rf $(O_FILES)

fclean: clean
	@echo "Cleaning binary..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

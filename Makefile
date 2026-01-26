# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jdong <jdong@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2026/01/18 14:58:29 by jdong         #+#    #+#                  #
#    Updated: 2026/01/26 13:36:08 by jingyandong   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = src
OBJ_DIR := obj

SRC = $(addprefix $(SRC_DIR)/, main.c exit_func.c getter_setter.c \
								init.c routines.c utils.c parse.c libft.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

FLAGS = -Werror -Wextra -Wall -pthread
HEADERS := -Iinclude

all: $(NAME)

# %.o: %.c
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	cc $(FLAGS) $(HEADERS) -c $< -o $@ 

$(NAME): $(OBJ)
	cc $(HEADERS) $(FLAGS) $(OBJ) $(LIBFT) -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	@rmdir $(OBJ_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
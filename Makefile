# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jdong <jdong@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2026/01/18 14:58:29 by jdong         #+#    #+#                  #
#    Updated: 2026/01/21 19:44:40 by jdong         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = src
OBJ_DIR := obj
LIBFT_DIR = libft

SRC = $(addprefix $(SRC_DIR)/, main.c exit_func.c getter_setter.c init.c routines.c utils.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

FLAGS = -Werror -Wextra -Wall -pthread
HEADERS := -Iinclude -I$(LIBFT_DIR)

LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

# %.o: %.c
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	cc $(FLAGS) $(HEADERS) -c $< -o $@ 

$(NAME): $(OBJ)
	cc $(HEADERS) $(FLAGS) $(OBJ) $(LIBFT) -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

clean:
	@$(MAKE) -s -C $(LIBFT_DIR) clean --no-print-directory
	rm -f $(OBJ)

fclean: clean
	@$(MAKE) -s -C $(LIBFT_DIR) fclean --no-print-directory
	@rmdir $(OBJ_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 
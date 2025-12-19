NAME = philo

SRC_DIR = src
OBJ_DIR := obj
LIBFT_DIR = libft

SRC = $(addprefix $(SRC_DIR)/, main.c exit_func.c init.c routines.c locks.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

FLAGS = -Werror -Wextra -Wall -pthread
HEADERS := -Iinclude -I$(LIBFT_DIR)

LIBFT = $(LIBFT_DIR)/libft.a

all: buildlib $(NAME)

# %.o: %.c
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	cc $(FLAGS) $(HEADERS) -c $< -o $@ 

$(NAME): $(OBJ)
	cc $(HEADERS) $(FLAGS) $(OBJ) $(LIBFT) -o $@

buildlib:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@rmdir $(OBJ_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all buildlib clean fclean re 
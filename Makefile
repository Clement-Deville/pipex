NAME = $(BIN_DIR)pipex

NAME_B = $(BIN_DIR)pipex_bonus

CC = cc

FLAGS = -Wall -Wextra -Werror

DEBUG = -g

SRCS_FILES =	main	\
				parse	\
				commands	\
				do	\
				utils	\
				redirection	\
				start_piping	\
				fd_utils	\

SRCS_FILES_BONUS =	main_bonus	\
					commands_bonus	\
					parse_bonus	\
					here_doc_bonus	\
					do_bonus	\
					utils_bonus	\
					redirection_bonus	\
					start_piping_bonus	\
					fd_utils_bonus	\


INCLUDES_FILES = pipex

SOURCE_DIR =	./src/mandatory/
SOURCE_BONUS_DIR = ./src/bonus/
INCLUDES_DIR =	./include/
OBJS_DIR =		./obj/
OBJS_BONUS_DIR = ./obj/
BIN_DIR =		./bin/
LIB_DIR =		./lib/
TEST_DIR =		./test/
MANDATORY_DIR =	mandatory/

LIBFT_DIR = $(LIB_DIR)/libft

SOURCES =	$(addprefix $(SOURCE_DIR), $(addsuffix .c, $(SRCS_FILES)))
INCLUDES =	$(addprefix $(INCLUDES_DIR), $(addsuffix .h, $(INCLUDES_FILES)))
OBJS =		$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_FILES)))
OBJS_B =	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_FILES_BONUS)))

.PHONY: all clean fclean re bonus norminette

all: $(NAME) $(NAME_B)

bonus: $(NAME_B)

$(OBJS_DIR)%.o : $(SOURCE_DIR)%.c
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(FLAGS) $(DEBUG) -I./lib/libft/INCLUDES -I$(INCLUDES_DIR) -c $< -o $@

$(OBJS_BONUS_DIR)%.o : $(SOURCE_BONUS_DIR)%.c
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(FLAGS) $(DEBUG) -I./lib/libft/INCLUDES -I$(INCLUDES_DIR) -c $< -o $@

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(FLAGS) $(OBJS) $(DEBUG) -lft -L$(LIBFT_DIR) -o $(NAME)
	@echo "\nMandatory part compiled !\n"

$(NAME_B): $(OBJS_B)
	make -C $(LIBFT_DIR)
	$(CC) $(FLAGS) $(OBJS_B) $(DEBUG) -lft -L$(LIBFT_DIR) -o $(NAME_B)
	@echo "\nBonus Compiled !\n"

clean:
	rm -rf $(OBJS_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(BIN_DIR)
	make fclean -C $(LIBFT_DIR)

re: fclean all

norminette:
			norminette ./src
			norminette ./include

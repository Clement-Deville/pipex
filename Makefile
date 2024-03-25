NAME = pipex

NAME_B = pipex_bonus

CC = cc

FLAGS = -Wall -Wextra -Werror

DEBUG = -g

SRCS_FILES =	main	\
				check_command_access	\
				exec_cmd	\
				parse	\
				do_unlink	\
				do_pipe		\
				do_dup2	\
				do_close	\
				utils	\
				redirection	\
				start_piping	\
				wait_for_all	\
				fd_utils	\
				get_next_line	\
				get_next_line_utils	\


SRCS_FILES_BONUS =	main_bonus	\
					print_commands	\
					parse_commands	\
					free_commands	\
					check_command_access	\
					exec_cmd	\
					parse	\
					do_unlink	\
					do_pipe		\
					do_dup2	\
					do_close	\
					utils	\
					redirection	\
					start_piping	\
					wait_for_all	\
					fd_utils	\
					get_next_line	\
					get_next_line_utils	\


INCLUDES_FILES = pipex

SOURCE_DIR =	./src/
INCLUDES_DIR =	./include/
OBJS_DIR =		./obj/
BIN_DIR = 		./bin/
LIB_DIR =		./lib/
TEST_DIR = 		./test/
MANDATORY_DIR = mandatory/

LIBFT_DIR = $(LIB_DIR)/libft

SOURCES =	$(addprefix $(SOURCE_DIR), $(addsuffix .c, $(SRCS_FILES)))
INCLUDES =	$(addprefix $(INCLUDES_DIR), $(addsuffix .h, $(INCLUDES_FILES)))
OBJS =		$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_FILES)))
OBJS_B = 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_FILES_BONUS)))

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $(OBJS) $(DEBUG) -lft -L$(LIBFT_DIR) -o $(BIN_DIR)$(NAME)
	@echo "pipex Done !"

$(NAME_B): $(OBJS_B)
	make -C $(LIBFT_DIR)
	mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $(OBJS_B) $(DEBUG) -lft -L$(LIBFT_DIR) -o $(BIN_DIR)$(NAME_B)
	@echo "pipex_bonus Done !"

$(OBJS_DIR)%.o : $(SOURCE_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(FLAGS) $(DEBUG) -I./lib/libft/INCLUDES -I$(INCLUDES_DIR) -c $< -o $@

all: $(NAME)

bonus: $(NAME_B)

clean:
	rm -rf $(OBJS_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(BIN_DIR)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re bonus

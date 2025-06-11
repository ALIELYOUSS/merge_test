SRC = src/parser/syntax_errors_utils.c src/parser/syntax_errors.c src/main.c src/utils/libft/libft_utils.c src/utils/libft/libft_utils1.c src/utils/prompt_utils.c src/tokenizer/get_word.c src/tokenizer/tokenize.c \
    src/tokenizer/quotes_error.c src/cmd_builder/cmd_builder.c src/cmd_builder/redirections.c src/cmd_builder/cmd_builder_utils.c $(wildcard execution/*.c) $(wildcard built_in/*.c)

OBJ = $(SRC:.c=.o)

# OBJ_BONUS = $(SRC_BONUS:.c=.o)

CC = cc

FLAGS = -Wall -Wextra -Werror 
NAME = minishell

# NAME_BONUS = minishell_bonus

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -L/usr/local/lib -I/usr/local/include -lreadline
#-I$(HOME)/.local/include -L$(HOME)/.local/lib -lreadline

bonus: $(NAME_BONUS)

$(NAME_BONUS):
	$(CC) $(FLAGS) $(OBJ_BONUS) -o $(NAME_BONUS)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re:fclean all

.PHONY: clean
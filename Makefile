SRC = src/parser/syntax_errors_utils.c src/parser/syntax_errors.c src/main.c src/utils/libft/libft_utils.c src/utils/libft/libft_utils1.c src/utils/prompt_utils.c src/tokenizer/get_word.c src/tokenizer/tokenize.c \
    src/tokenizer/quotes_error.c src/cmd_builder/cmd_builder.c src/cmd_builder/redirections.c src/cmd_builder/cmd_builder_utils.c $(wildcard execution/*.c) $(wildcard built_in/*.c) $(wildcard get_next_line/*.c)

OBJ = $(SRC:.c=.o)

CC = cc

FLAGS = -Wall -Wextra -Werror  -g3

NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -L/usr/local/lib -I/usr/local/include -lreadline

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:fclean all

.PHONY: clean
CC = cc

CFLAGS = # -Wall -Wextra -Werror

MIMI_SRC = main.c

MIMI_OBJ = $(MIMI_SRC:.c=.o)

NAME = minishell

LIBFT = libft.a

LIBFT_SRC = $(wildcard $(LIBFT_DIR)/*.c)

LIBFT_OBJ = $(wildcard $(LIBFT_DIR)/*.o)

LIBFT_DIR = coreutils

all: $(NAME)

$(NAME): $(MIMI_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(MIMI_OBJ)  -o $@ -lreadline $(LIBFT)

$(LIBFT): $(LIBFT_SRC)
	make -C coreutils all
	mv coreutils/libft.a .

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(MIMI_OBJ)
	make -C coreutils clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)

re: clean all

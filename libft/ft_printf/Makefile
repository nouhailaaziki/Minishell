CC = cc

NAME = ../libftprintf.a

SRC =  ft_printchar.c ft_printstr.c ft_printnbr.c ft_puthex.c ft_putptr.c ft_putuint.c ft_printf.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all :$(NAME)

$(NAME): $(OBJ)
	ar -rc $(NAME) $^

OBJ: $(OBJ)

%.o : %.c ft_printf.h
	$(CC) -c $(CFLAGS) $< -o $@

re: fclean all

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

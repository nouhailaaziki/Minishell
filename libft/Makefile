CC = cc

CFLAGS =  -g -Wall -Wextra -Werror

RM = rm -f

LIBFT_SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
			   ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
			   ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
			   ft_substr.c ft_tolower.c ft_toupper.c ft_strjoin.c ft_strtrim.c ft_putchar_fd.c ft_pow.c \
			   ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_striteri.c ft_strmapi.c ft_itoa.c ft_split.c \
			   ft_abs.c ft_count_words.c ft_factors_count.c ft_is_duplicated.c ft_is_int.c ft_is_int_array.c \
			   ft_is_sorted.c ft_is_uint.c ft_isspace.c ft_lst_new.c ft_lstadd_front.c ft_lstlast.c ft_lstsize.c\
			   ft_str_isspace.c ft_super_strlen.c ft_atoi_modified.c get_next_line/get_next_line.c

PRINTF_SRC = ft_printf/ft_printchar.c ft_printf/ft_puthex.c ft_printf/ft_printnbr.c ft_printf/ft_putptr.c\
			 ft_printf/ft_printstr.c ft_printf/ft_putuint.c ft_printf/ft_printf.c

PRINTF_OBJ = $(PRINTF_SRC:.c=.o)

LIBFT_OBJ = $(LIBFT_SRC:.c=.o)

LIBFTPRINTF= libftprintf.a

NAME = libft.a

all: $(NAME)

$(NAME): $(LIBFT_OBJ) $(PRINTF_OBJ)
	ar rc $(NAME) $^

$(PRINTF_OBJ): $(PRINTF_SRC) ft_printf/ft_printf.h
	make -C ft_printf OBJ

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(LIBFT_OBJ)
	make -C ft_printf clean

fclean: clean
	$(RM) $(NAME) libftprintf.a

re: fclean all

.PHONY:clean

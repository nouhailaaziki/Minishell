
RED = \033[0;31m
BOLD = \033[1m
GREEN = \033[0;32m
BLUE = \x1b[34m
YELLOW = \033[0;33m
RESET = \033[0m

RM = rm -rf

COMPILER = cc

CFLAGS = -g3  -O0  -Wall -Wextra -Werror

LIBFT = libft.a

LIBFT_SRC = libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c \
			   libft/ft_isprint.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memset.c libft/ft_strchr.c \
			   libft/ft_strdup.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strlen.c libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c \
			   libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_putchar_fd.c libft/ft_pow.c \
			   libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_striteri.c libft/ft_strmapi.c libft/ft_itoa.c libft/ft_split.c \
			   libft/ft_abs.c libft/ft_count_words.c libft/ft_factors_count.c libft/ft_is_duplicated.c libft/ft_is_int.c libft/ft_is_int_array.c \
			   libft/ft_is_sorted.c libft/ft_is_uint.c libft/ft_isspace.c libft/ft_lst_new.c libft/ft_lstadd_front.c libft/ft_lstlast.c libft/ft_lstsize.c\
			   libft/ft_str_isspace.c libft/ft_super_strlen.c libft/ft_atoi_modified.c libft/get_next_line/get_next_line.c \
			   libft/ft_printf/ft_printchar.c libft/ft_printf/ft_puthex.c libft/ft_printf/ft_printnbr.c libft/ft_printf/ft_putptr.c\
			   libft/ft_printf/ft_printstr.c libft/ft_printf/ft_putuint.c libft/ft_printf/ft_printf.c 

PARSING = parsing/tokenization_utils.c parsing/handlers.c parsing/misc_utils.c \
		  parsing/lexer_utils.c parsing/tree_utils.c parsing/parser_utils.c parsing/ft_free.c


EXECUTION =	execution/builtins/cd.c execution/builtins/pwd.c execution/builtins/echo.c execution/builtins/exit.c execution/builtins/unset.c \
			execution/builtins/export.c execution/builtins/export_utils.c execution/builtins/env.c execution/environment/fill_env_list.c execution/environment/free_env_list.c \
			execution/environment/get_env_arr.c execution/events/puterror.c execution/events/errno_manager.c execution/events/display_intro.c execution/builtins/manage_builtins.c \
			execution/garbage_collector/free_all_tracked.c execution/garbage_collector/nalloc.c execution/utilities/ft_arrlen.c execution/utilities/ft_atoi.c execution/utilities/ft_isallchar.c \
			execution/utilities/ft_isdigit.c execution/utilities/ft_memset.c execution/utilities/ft_strchr.c execution/utilities/ft_strcmp.c execution/utilities/ft_strncmp.c execution/utilities/ft_strlen.c \
			execution/utilities/na_calloc.c execution/utilities/na_itoa.c execution/utilities/na_split.c execution/utilities/na_strdup.c execution/utilities/na_strjoin.c execution/utilities/na_substr.c \
			execution/utilities/strict_atoi.c execution/utilities/ft_putstr_fd.c execution/utilities/na_mkstemp.c execution/redirection/redirs.c execution/executor/execute.c main.c\
			execution/executor/execute_command.c execution/executor/execute_pipe.c  execution/redirection/heredocs_handler.c execution/redirection/heredocs_manager.c \
			execution/signals/handle_sigint.c execution/signals/setup_signals.c execution/signals/terminal_control.c execution/executor/execute_parentheses.c

EXEC = ${EXECUTION:.c=.o}

PARSE = $(PARSING:.c=.o)

LIBFT_OBJ = $(LIBFT_SRC:.c=.o)

HEADER = execution/launchpad.h libft/libft.h

NAME = minishell

all: ${NAME}

${NAME} : $(LIBFT) ${PARSE} ${EXEC}
	@echo "${YELLOW} ${BOLD}➤ Launching compilation...${RESET}"
	${COMPILER} ${CFLAGS} $(PARSE) ${EXEC} -o $@ $(LIBFT) -lreadline
	@echo "${GREEN} ${BOLD}➤ ${NAME} successfully compiled ✓${RESET}"


$(LIBFT): $(LIBFT_SRC)
	@echo "${YELLOW} ${BOLD}➤ Launching $(LIBFT) compilation...${RESET}"
	make -C libft all
	@echo "${GREEN} ${BOLD}➤ ${LIBFT} successfully compiled ✓${RESET}"
	mv libft/libft.a .


%.o : %.c ${HEADER}
	${COMPILER} ${CFLAGS} -c $< -o $@

clean:
	${RM} ${EXEC}
	${RM} ${PARSE}
	make -C libft clean
	@echo "${BLUE} ${BOLD}Object files removed ✓${RESET}"

fclean: clean
	${RM} ${NAME} $(LIBFT)
	@echo "${GREEN} ${BOLD}Executable removed ✓${RESET}"

re: fclean all

.PHONY: clean

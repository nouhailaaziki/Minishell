COMPILER = cc

CFLAGS = -g  # -Wall -Wextra -Werror # -fsanitize=address -g3


LIBFT = libft.a

LIBFT_DIR = libft

LIBFT_SRC = $(wildcard $(LIBFT_DIR)/*.c)

LIBFT_OBJ = $(wildcard $(LIBFT_DIR)/*.o)


RED = \033[0;31m
BOLD = \033[1m
GREEN = \033[0;32m
BLUE = \x1b[34m
YELLOW = \033[0;33m
RESET = \033[0m
MINI_SRC = tokenization_utils.c handlers.c misc_utils.c lexer_utils.c tree_utils.c parser_utils.c

EXECUTION =	execution/builtins/cd.c \
			execution/builtins/pwd.c \
			execution/builtins/echo.c \
			execution/builtins/exit.c \
			execution/builtins/unset.c \
			execution/builtins/export.c \
			execution/builtins/export_utils.c \
			execution/builtins/env.c \
			execution/environment/fill_env_list.c \
			execution/environment/free_env_list.c \
			execution/environment/get_env_arr.c \
			execution/events/puterror_to_exit.c \
			execution/events/puterror.c \
			execution/events/errno_manager.c \
			execution/events/display_intro.c \
			execution/garbage_collector/free_all_tracked.c \
			execution/garbage_collector/nalloc.c \
			execution/utilities/ft_arrlen.c \
			execution/utilities/ft_atoi.c \
			execution/utilities/ft_isallchar.c \
			execution/utilities/ft_isdigit.c \
			execution/utilities/ft_memset.c \
			execution/utilities/ft_strchr.c \
			execution/utilities/ft_strcmp.c \
			execution/utilities/ft_strncmp.c \
			execution/utilities/ft_strlen.c \
			execution/utilities/na_calloc.c \
			execution/utilities/na_itoa.c \
			execution/utilities/na_split.c \
			execution/utilities/na_strdup.c \
			execution/utilities/na_strjoin.c \
			execution/utilities/na_substr.c \
			execution/utilities/strict_atoi.c \
			execution/utilities/ft_putstr_fd.c \
			execution/redirection/redirs.c \
			execution/executor.c main.c\
			$(MINI_SRC)



EXEC = ${EXECUTION:.c=.o}

NAME = minishell

HEADER = exeecution/launchpad.h libft/libft.h

all: ${NAME}
	./minishell
${NAME} : ${EXEC} $(LIBFT)
	@echo "${YELLOW} ${BOLD}➤ Launching compilation...${RESET}"
	${COMPILER} ${CFLAGS} ${EXEC} -o $@ $(LIBFT) -lreadline -ltermcap
	@echo "${GREEN} ${BOLD}➤ ${NAME} successfully compiled ✓${RESET}"

$(LIBFT): $(LIBFT_SRC)
	make -C libft all
	mv libft/libft.a .


%.o : %.c ${HEADER}
	${COMPILER} ${CFLAGS} -c $< -o $@

clean:
	${RM} ${EXEC}
	@echo "${BLUE} ${BOLD}Object files removed ✓${RESET}"
	make -C libft clean

fclean: clean
	${RM} ${NAME} $(LIBFT)
	@echo "${GREEN} ${BOLD}Executable removed ✓${RESET}"

re: fclean all

.PHONY: clean

COMPILER = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

RED = \033[0;31m
BOLD = \033[1m
GREEN = \033[0;32m
BLUE = \x1b[34m
YELLOW = \033[0;33m
RESET = \033[0m

EXECUTION =	builtins/cd.c \
			builtins/pwd.c \
			builtins/echo.c \
			builtins/exit.c \
			builtins/unset.c \
			builtins/export.c \
			builtins/export_utils.c \
			builtins/env.c \
			environment/fill_env_list.c \
			environment/free_env_list.c \
			environment/get_env_arr.c \
			events/puterror_to_exit.c \
			events/errno_manager.c \
			garbage_collector/free_all_tracked.c \
			garbage_collector/nalloc.c \
			parsing/lexer.c \
			parsing/parser.c \
			parsing/parse_input.c \
			utilities/ft_arrlen.c \
			utilities/ft_atoi.c \
			utilities/ft_isallchar.c \
			utilities/ft_isdigit.c \
			utilities/ft_memset.c \
			utilities/ft_strchr.c \
			utilities/ft_strcmp.c \
			utilities/ft_strncmp.c \
			utilities/ft_strlen.c \
			utilities/na_calloc.c \
			utilities/na_itoa.c \
			utilities/na_split.c \
			utilities/na_strdup.c \
			utilities/na_strjoin.c \
			utilities/na_substr.c \
			utilities/strict_atoi.c \
			utilities/ft_putstr_fd.c \
			executor.c main.c



EXEC = ${EXECUTION:.c=.o}

NAME = minishell

HEADER = headers/launchpad.h

all: ${NAME}

${NAME} : ${EXEC}
	@echo "${YELLOW} ${BOLD}➤ Launching compilation...${RESET}"
	${COMPILER} ${CFLAGS} ${EXEC} -o $@ -lreadline -ltermcap
	@echo "${GREEN} ${BOLD}➤ ${NAME} successfully compiled ✓${RESET}"


%.o : %.c ${HEADER}
	${COMPILER} ${CFLAGS} -c $< -o $@

clean:
	${RM} ${EXEC}
	@echo "${BLUE} ${BOLD}Object files removed ✓${RESET}"

fclean: clean
	${RM} ${NAME}
	@echo "${GREEN} ${BOLD}Executable removed ✓${RESET}"

re: fclean all

.PHONY: clean
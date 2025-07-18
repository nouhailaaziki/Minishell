
RED = \033[0;31m
BOLD = \033[1m
GREEN = \033[0;32m
BLUE = \x1b[34m
YELLOW = \033[0;33m
RESET = \033[0m

RM = rm -rf

CC = cc

CFLAGS = -g -Wall -Wextra

UTILITIES = utilities/ft_bzero.c utilities/ft_calloc.c utilities/ft_isalnum.c utilities/ft_isalpha.c utilities/ft_isascii.c utilities/ft_isdigit.c utilities/ft_isspace.c \
			utilities/ft_strdup.c utilities/ft_substr.c utilities/ft_str_isspace.c utilities/na_arrlen.c utilities/ft_atoi.c utilities/ft_isallchar.c \
			utilities/ft_memset.c utilities/ft_strchr.c utilities/ft_strcmp.c utilities/ft_strncmp.c utilities/ft_strlen.c utilities/ft_strjoin.c utilities/ft_split_args.c\
			utilities/na_calloc.c utilities/na_itoa.c utilities/na_split.c utilities/na_strdup.c utilities/na_strjoin.c utilities/na_substr.c utilities/ft_memcpy.c\
			utilities/na_atoi.c utilities/na_mkstemp.c utilities/ft_putchar_fd.c utilities/ft_putstr_fd.c utilities/ft_putendl_fd.c utilities/ft_itoa.c utilities/get_next_line.c \
			utilities/close_fd.c

PARSING = parsing/tokenization_utils.c parsing/handlers.c parsing/parenthes_utils.c \
		  parsing/str_lexer_utils.c parsing/tree_utils.c parsing/tree_utils_misc.c parsing/parser_utils.c\
		  parsing/ft_free.c parsing/advanced_tree_utils.c parsing/errors.c parsing/token_utils.c\
		  parsing/expand/expand_cmd.c parsing/expand/expand_utils.c parsing/expand/key_utils.c \
		  parsing/expand/expand_quotes.c parsing/expand/handle_expand_utils.c parsing/expand/expand_redirs.c \
		  basic_visualiser.c advanced_visualizer.c misc_utils.c main.c

EXECUTION =	execution/builtins/pwd.c execution/builtins/echo.c execution/builtins/exit.c execution/builtins/unset.c execution/builtins/path_build.c \
			execution/builtins/export.c execution/builtins/export_utils.c execution/builtins/env.c execution/environment/env_setup.c execution/executor/dry_run_fork.c \
			execution/environment/get_env_arr.c execution/events/puterror.c execution/events/errno_manager.c execution/events/display_intro.c \
			execution/builtins/manage_builtins.c  execution/executor/execute.c execution/redirection/heredocs_manager.c execution/builtins/path_utils.c\
			execution/garbage_collector/free_all_tracked.c execution/garbage_collector/nalloc.c execution/redirection/redirs.c execution/builtins/refresh_pwd.c\
			execution/executor/execute_command.c execution/executor/execute_pipe.c  execution/redirection/heredocs_handler.c execution/signals/setup_signals.c \
			execution/signals/handle_sigint.c execution/signals/terminal_control.c execution/executor/execute_parentheses.c execution/environment/env_utils.c \
			execution/executor/execute_command_utils.c utilities/ft_strrchr.c execution/environment/get_env_value.c execution/builtins/cd.c execution/environment/env_update.c \
			execution/wildcards/handle_wildcards.c execution/wildcards/wildcards_utils.c

EXEC = ${EXECUTION:.c=.o}

PARSE = $(PARSING:.c=.o)

UTILS = $(UTILITIES:.c=.o)

HEADER = launchpad.h

NAME = minishell

all: ${NAME}

${NAME} :  ${PARSE} ${EXEC} ${UTILS}
	@echo "${YELLOW} ${BOLD}➤ Launching compilation...${RESET}"
	${CC} ${CFLAGS} $(PARSE) ${EXEC} ${UTILS} -o $@ -lreadline
	@echo "${GREEN} ${BOLD}➤ ${NAME} successfully compiled ✓${RESET}"

%.o : %.c ${HEADER}
	${CC} ${CFLAGS} -c $< -o $@

clean:
	${RM} ${PARSE} ${EXEC} ${UTILS}
	@echo "${BLUE} ${BOLD}Object files removed ✓${RESET}"

fclean: clean
	${RM} ${NAME}
	@echo "${GREEN} ${BOLD}Executable removed ✓${RESET}"

re: fclean all

.PHONY: clean

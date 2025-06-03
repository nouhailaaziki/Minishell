COMPILER = cc

CFLAGS = -Wall -Wextra -Werror # -fsanitize=address -g3


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
MINI_SRC = tokenization_utils.c handlers.c misc_utils.c base_utils.c tree_utils.c

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
			events/puterror.c \
			events/errno_manager.c \
			events/display_intro.c \
			garbage_collector/free_all_tracked.c \
			garbage_collector/nalloc.c \
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
			redirection/redirs.c \
			executor.c main.c\
			$(MINI_SRC)



EXEC = ${EXECUTION:.c=.o}

NAME = minishell

HEADER = headers/launchpad.h libft/libft.h

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
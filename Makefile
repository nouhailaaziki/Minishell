COMPILER = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

SRC =	minishell.c fill_env_list.c executor.c builtins/echo.c \
		builtins/pwd.c builtins/exit.c builtins/cd.c builtins/env.c \
		builtins/unset.c builtins/export.c builtins/export_utils.c

OBJ = ${SRC:.c=.o}

NAME = Executable

LIBFT = libft/libft.a

HEADER = launchpad.h libft/libft.h

all: ${NAME}

${NAME} : ${OBJ} ${LIBFT}
	@echo "${YELLOW}🚀 Launching compilation...${RESET}"
	${COMPILER} ${CFLAGS} ${OBJ} ${LIBFT} -o ${NAME}
	@echo "${GREEN}✅ ${NAME} successfully compiled!${RESET}"

%.o : %.c ${HEADER}
	${COMPILER} ${CFLAGS} -c $< -o $@

${LIBFT}:
	make -C libft

clean:
	${RM} ${OBJ}
	make clean -C libft
	@echo "${RED}🗑 Object files removed!${RESET}"

fclean: clean
	${RM} ${NAME}
	make fclean -C libft
	@echo "${RED}🔥 Executable removed!${RESET}"

re: fclean all

.PHONY: all clean fclean re
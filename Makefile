COMPILER = cc

CFLAGS = -Wall -Wextra -Werror 
#-fsanitize=address -g3

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

SRC =	builtins/cd.c builtins/pwd.c \
		builtins/env.c builtins/exit.c \
		builtins/unset.c builtins/export.c \
		builtins/echo.c builtins/env_list.c \
		utilities/sentinel.c utilities/print_fd.c \
		minishell.c executor.c builtins/export_utils.c \
		utilities/string_forge.c utilities/string_weaver.c \
		events/free_env_list.c

OBJ = ${SRC:.c=.o}

NAME = Executable

HEADER = headers/launchpad.h headers/pixie.h

all: ${NAME}

${NAME} : ${OBJ}
	@echo "${YELLOW}🚀 Launching compilation...${RESET}"
	${COMPILER} ${CFLAGS} ${OBJ} ${LIBFT} -o ${NAME}
	@echo "${GREEN}✅ ${NAME} successfully compiled!${RESET}"

%.o : %.c ${HEADER}
	${COMPILER} ${CFLAGS} -c $< -o $@

clean:
	${RM} ${OBJ}
	@echo "${RED}🗑 Object files removed!${RESET}"

fclean: clean
	${RM} ${NAME}
	@echo "${RED}🔥 Executable removed!${RESET}"

re: fclean all

.PHONY: all clean fclean re
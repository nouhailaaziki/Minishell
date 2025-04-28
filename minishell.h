#ifndef MINISHELL_H

#include <unistd.h>
#include <readline/readline.h>
#include "coreutils/libft.h"

typedef struct s_token
{
	char *value;
	char *type;
	struct s_token *next;
} t_token;

int ft_is_operator(int c);
int ft_is_bonus_operator(char *str);
int token_counter(char *str);
void free_arr(char **ptr);
#endif

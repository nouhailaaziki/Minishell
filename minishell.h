#ifndef MINISHELL_H

#include <unistd.h>
#include <readline/readline.h>

typedef struct s_token
{
	char *value;
	char *type;
	struct s_token *next;
} t_token;

#endif

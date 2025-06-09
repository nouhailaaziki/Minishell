/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchpad.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 10:54:18 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/09 18:03:18 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCHPAD_H
# define LAUNCHPAD_H

/*---------------------Header inclusion directive---------------------*/
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <sys/stat.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

/*-----------------------Format and Color Macros----------------------*/
# define BOLD "\033[1m"
# define ORANGE "\x1b[38;5;214m"
# define PINK "\x1b[95m"

/*-----------------------The kind of each token-----------------------*/
typedef enum e_token_type
{
	TOKEN_WORD = 1,
	TOKEN_ARG,
	TOKEN_PAREN,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_PIPE,
	TOKEN_REDIR,
	R_FILE
} t_token_type;

typedef enum e_redir_type
{
	REDIR_IN = 10,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_NONE
} t_redir_type;

/*--------------------Linked list of parsed tokens--------------------*/
typedef struct s_token
{
	size_t			position;
	char			*value;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
} t_token;

/*--------------------Redirection info for a command------------------*/
typedef struct s_redir
{
	size_t				index;
	t_token_type		type;
	char				*file;
	int					fd;
	int					flag;
	struct s_redir		*next;
}	t_redir;

/*---------------------------Node type enum---------------------------*/
typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_PARENTHS
}	t_node_type;

/*----------------Linked list of environment variables----------------*/
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/*-------------------Garbage collector node struct--------------------*/
typedef struct s_gcnode
{
	void			*address;
	struct s_gcnode	*next;
}	t_gcnode;

/*---------------Linked list of executable search paths---------------*/
typedef struct s_path
{
	void			*path;
	struct s_path	*next;
}	t_path;

/*--------------------------Tree node struct--------------------------*/
typedef struct s_tree
{
	t_node_type			type;
	char				**cmd;
	size_t				argc;
	int					redir_count;
	t_redir				*redirs;
	t_redir				*redirs_before;
	t_redir				*redirs_after;
	int					is_ambiguous;
	struct s_tree		*left;
	struct s_tree		*right;
}	t_tree;

/*-------------------------Execution manager--------------------------*/
void		executor(t_tree *ast, t_env **env);

/*-----------------------Environment fonctions------------------------*/
t_env		*env_node(char *envp);
char		**get_env_arr(t_env *env_list);
void		upp_shlvl(t_env *node, int nbr);
void		build_env(t_env **env_list, char **envp);

/*-------------------------Builtins fonctions-------------------------*/
int			pwd(void);
int			echo(char **cmd);
int			env(t_env *env_list);
int			cd(char **cmd, t_env **env_list);
int			unset(t_env **env_list, char **cmd);
int			export(char **cmd, t_env **env_list);
void		run_exit(char **cmd, int exit_status);
void		handle_argument(t_env **env_list, char *cmd);
t_env		*create_node(char *argv, size_t key_len, char *sign);
void		sort_env_list(t_env **env_list);
int			check_validity(char	*argv, char *cmd);
void		add_value(t_env	**env_list, char *argv, char *key);
void		update_env(t_env **env_list, char *argv, char *key, int start);
void		ft_putstr_fd(char *s, int fd);

/*--------------------Garbage collector fonctions---------------------*/
void		*nalloc(size_t __size);
void		free_all_tracked(void);
t_gcnode	**memory_tracker(void);

/*-------------------Utilities from libft (Updated)-------------------*/
char		*na_itoa(int n);
int			ft_isdigit(int c);
int			ft_arrlen(char **arr);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
char		*na_strdup(const char *s);
long		strict_atoi(const char *str);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strchr(const char *s, int c);
char		**na_split(char const *s, char c);
int			ft_isallchar(const char *str, char c);
void		*na_calloc(size_t count, size_t size);
void		*ft_memset(void *b, int c, size_t len);
char		*na_strjoin(char const *s1, char const *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*na_substr(char const *s, unsigned int start, size_t len);

/*---------------------------Redirection implement---------------------------*/
int	handle_redirs(t_redir *redir);

/*----------------------------------Events-----------------------------------*/
void		display_intro(void);
void		is_it_dir(char *cmd);
void		errno_manager(char	*cmd);
int			puterror(char *cmd, char *error);
void		puterror_to_exit(char *cmd, char *error, int ex);
/*---------------------Parsing STUFF------------------------------------------*/

t_token *ft_token_search(t_token **head, int type);
void link_redir(t_redir **list, t_redir *new_redir);
int handle_quotes(char *str, char quote_type);
int ft_before_x(char *str, int (*f)(char *s));
int ft_syntax_err(char *str, t_token **head);
int lexer(t_token **head, char *line_read);
void advanced_token_lexer(t_token **head);
t_redir *redir_list_maker(t_token **head);
t_tree *create_tree_node(int type,int cmd_count);
t_redir *redir_maker(t_token *data);
int ft_is_bonus_operator(char *str);
int ft_syntax_analyzer(char *str);
int handle_parentheses(char *str);
void free_tokens(t_token **head);
int ft_isparentheses(char *c);
int ft_is_operator(char *c);
int operator_len(char *str);
int token_lexer(char *str);
int parser(t_token **head);
int skip_spaces(char *str);
int count_chars(char *str);
int ft_is_redir(char *c);
char ft_isquote(char c);

// ! REMOVE THS LATER
void print_tokens(t_token **head);
void print_tree(t_tree *tree);
void print_redirs(t_redir *redir);




#endif

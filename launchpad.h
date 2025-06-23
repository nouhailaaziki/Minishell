/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchpad.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 10:54:18 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/23 09:51:27 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCHPAD_H
#define LAUNCHPAD_H

/*---------------------Header inclusion directive---------------------*/
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

/*-----------------------Format and Color Macros----------------------*/
#define BOLD "\033[1m"
#define ORANGE "\x1b[38;5;214m"
#define PINK "\x1b[95m"

/*-----------------------The kind of each token-----------------------*/
typedef enum e_token_type
{
	TOKEN_WORD = 1,
	TOKEN_ARG,
	TOKEN_PAREN,
	TOKEN_PAREN_LEFT,
	TOKEN_PAREN_RIGHT,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_PIPE,
	TOKEN_REDIR,
	R_FILE,
	REDIR_IN = 20,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
} t_token_type;

/*--------------------Linked list of parsed tokens--------------------*/
typedef struct s_token
{
	int position;
	char *value;
	int type;
	char *err_location;
	struct s_token *next;
	struct s_token *prev;

} t_token;

/*--------------------Redirection info for a command------------------*/
typedef struct s_redir
{
	size_t			index;
	t_token_type 	type;
	char			*file;
	int				fd;
	int				flag;
	struct s_redir	*next;
} t_redir;

/*---------------------------Node type enum---------------------------*/
typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_PARENTHS
} t_node_type;

/*----------------Linked list of environment variables----------------*/
typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

/*-------------------Garbage collector node struct--------------------*/
typedef struct s_gcnode
{
	void *address;
	struct s_gcnode *next;
} t_gcnode;

/*---------------Linked list of executable search paths---------------*/
typedef struct s_path
{
	void *path;
	struct s_path *next;
} t_path;

/*--------------------------Tree node struct--------------------------*/
typedef struct s_tree
{
	t_node_type type;
	char **cmd;
	size_t argc;
	t_redir *redirs;
	int is_ambiguous;
	struct s_tree *left;
	struct s_tree *right;
} t_tree;

typedef struct s_shell
{
	t_token *tokens, *current;
	t_env *env_list;
	t_tree *ast;
	char *line;
} t_shell;


/*-------------------------Execution manager--------------------------*/
void executor(t_tree *ast, t_env **env);

/*-----------------------Environment fonctions------------------------*/
t_env *env_node(char *envp);
char **get_env_arr(t_env *env_list);
void upp_shlvl(t_env *node, int nbr);
void build_env(t_env **env_list, char **envp);

/*-------------------------Builtins fonctions-------------------------*/
int pwd(void);
int echo(char **cmd);
int env(t_env *env_list);
int cd(char **cmd, t_env **env_list);
int unset(t_env **env_list, char **cmd);
int export(char **cmd, t_env **env_list);
void run_exit(char **cmd, int exit_status);
void handle_argument(t_env **env_list, char *cmd);
t_env *create_node(char *argv, size_t key_len, char *sign);
void sort_env_list(t_env **env_list);
int check_validity(char *argv, char *cmd);
void add_value(t_env **env_list, char *argv, char *key);
void update_env(t_env **env_list, char *argv, char *key, int start);
void ft_putstr_fd(char *s, int fd);

/*--------------------Garbage collector fonctions---------------------*/
void *nalloc(size_t __size);
void free_all_tracked(void);
t_gcnode **memory_tracker(void);

/*-------------------Utilities from libft (Updated)-------------------*/
char *na_itoa(int n);
int ft_isdigit(int c);
int ft_arrlen(char **arr);
int ft_atoi(const char *str);
size_t ft_strlen(const char *s);
char *na_strdup(const char *s);
long strict_atoi(const char *str);
int ft_strcmp(char *s1, char *s2);
char *ft_strchr(const char *s, int c);
char **na_split(char const *s, char c);
int ft_isallchar(const char *str, char c);
void *na_calloc(size_t count, size_t size);
void *ft_memset(void *b, int c, size_t len);
char *na_strjoin(char const *s1, char const *s2);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *na_substr(char const *s, unsigned int start, size_t len);

/*---------------------------Redirection implement---------------------------*/
int handle_redirs(t_redir *redir);

/*----------------------------------Events-----------------------------------*/
void display_intro(void);
void is_it_dir(char *cmd);
void errno_manager(char *cmd);
int puterror(char *cmd, char *error);
void puterror_to_exit(char *cmd, char *error, int ex);
/*-----------------------------execute fonctions-----------------------------*/
int execute_ast(t_tree *ast, t_env **env);
int execute_command(char **cmd, t_redir *redirs, t_env **env_list);
int execute_pipe(t_tree *ast, t_redir *redirs, t_env **env_list);

/*--------------------------------signals------------------------------------*/
void setup_signals_parent(void);
void setup_signals_child(void);
/*---------------------Parsing STUFF------------------------------------------*/
void init_shell(t_shell *shell);
int lexer(t_shell *shell, int status_flag);
void parentheses_lexer(t_token **head);
void link_token(t_token **head, t_token *node);
int handle_quotes(char *str, char quote_type);
void advanced_token_lexer(t_token **head);
int ft_syntax_analyzer(char *str);
int parentheses_counter(char *str);
int parentheses_counter_v2(t_token *head);
int handle_parentheses(t_token *head);
int operator_len(char *str);
int token_lexer(char *str);
int parser(t_shell shell);
int skip_spaces(char *str);
/*-----------Tree Stuff-------------------*/
t_tree *create_block(t_token **head, int count, int type);
void link_redir(t_redir **list, t_redir *new_redir);
t_token *ft_token_search(t_token *head, int type, int nav_flag);
t_tree *create_tree_node(int type, int cmd_count);
t_redir *redir_list_maker(t_token **head);
int block_arg_counter(t_token *head);
int sub_block_arg_counter(t_token *head);
t_token *find_PIPE(t_token *head, int nav_flag);
int block_identifier(t_token *head);
t_redir *redir_maker(t_token **data);
int count_chars(char *str);
/*---------------------Checkers-------------------*/
int ft_syntax_err(char *str);
int ft_before_x(char *str, int (*f)(char *s));
int ft_is_bonus_operator(char *str);
int ft_isparentheses(char *c);
int ft_is_operator(char *c);
int ft_is_redir(char *c);
char ft_isquote(char c);
/*-----------free-------------*/
void clear_memory(t_shell *shell);
void free_cmd(char **cmd);
void free_tree(t_tree **ast);
void free_tokens(t_token **head);
// ! REMOVE THS LATER
void print_tokens(t_token **head);
void print_redirs(t_redir *redir);
void print_tree(t_tree *tree);
/*-- -- -- -- -- -- -- -- -- -- -- -Tree Visualization Functions-- -- -- -- -- -- -- -- -- -- -- -*/

	/**
	 * @brief Main function to visualize the AST tree with colors and structure
	 * @param root Pointer to the root node of the AST
	 *
	 * Displays a detailed tree structure with:
	 * - Color-coded node types
	 * - Command arguments
	 * - Redirection information
	 * - Tree depth and node count
	 */
	void visualize_ast_tree(t_tree *root);

/**
 * @brief Print a simplified flat representation of the tree
 * @param node Current node to print
 * @param level Indentation level
 *
 * Displays a simple indented list showing the tree structure
 */
void print_flat_ast(t_tree *node, int level);

/**
 * @brief Export the AST to DOT format for graphviz visualization
 * @param root Pointer to the root node of the AST
 * @param filename Output filename for the DOT file
 *
 * Creates a .dot file that can be rendered with graphviz:
 * dot -Tpng filename.dot -o output.png
 */
void visualize_tokens(t_token *head);

#endif

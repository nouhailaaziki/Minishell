/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchpad.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 10:54:18 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/22 08:44:52 by noaziki          ###   ########.fr       */
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
# include <signal.h>
# include <dirent.h>
# include <stdbool.h>
# include <fnmatch.h>
# include <termios.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

/*-----------------------Format and Color Macros----------------------*/
# define BOLD "\033[1m"
# define ORANGE "\x1b[38;5;214m"
# define PINK "\x1b[95m"
# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define BHBLK "\e[1;90m"
# define BHRED "\e[1;91m"
# define BHGRN "\e[1;92m"
# define BHYEL "\e[1;93m"
# define BHBLU "\e[1;94m"
# define BHMAG "\e[1;95m"
# define BHCYN "\e[1;96m"
# define BHWHT "\e[1;97m"
# define RESET "\e[0m"

/*----------------------------global flag-----------------------------*/
int		g_sigint_received;

/*-----------------------The kind of each token-----------------------*/
typedef enum e_token_type
{
	TOKEN_WORD = 1,
	TOKEN_CMD,
	TOKEN_ARG,
	TOKEN_PAREN,
	TOKEN_PAREN_LEFT,
	TOKEN_PAREN_RIGHT,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_PIPE,
	TOKEN_REDIR,
	R_FILE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}	t_token_type;

/*--------------------Linked list of parsed tokens--------------------*/
typedef struct s_token
{
	int				position;
	char			*value;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_var
{
	char			*key;
	char			*value;
	int				key_len;
	int				value_len;
	int				expandable;
	struct s_var	*next;
}	t_var;
/*--------------------Redirection info for a command------------------*/
typedef struct s_redir
{
	size_t			index;
	t_token_type	type;
	char			*file;
	int				fd;
	int				fd_rd;
	int				fd_wr;
	int				flag;
	int				is_ambiguous;
	struct s_redir	*next;
}	t_redir;

/*---------------------------Node type enum---------------------------*/
typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_PARENTHESES
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
	t_node_type		type;
	char			**cmd;
	size_t			argc;
	t_redir			*redirs;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

/*--------------------------struct of tools---------------------------*/
typedef struct s_stash
{
	int				status;
	int				return_status;
	int				fork_failed;
	int				path_flag;
	int				exit_flag;
	char			*pwd_backup;
	char			*heredoc_store;
	int				heredoc_interrupted;
	int				is_parent_flag;
	t_env			**env_list;
	struct termios	orig_termios;
}	t_stash;

/*-------------------essential components of a shell------------------*/
typedef struct s_shell
{
	t_token	*tokens;
	t_token	*current;
	t_env	*env_list;
	t_tree	*ast;
	char	*line;
	t_stash	stash;
}	t_shell;

/*--------------------------wildcards tool---------------------------*/
typedef struct s_match_data
{
	char	**matches;
	size_t	capacity;
	size_t	count;
}	t_match_data;

/*------------------------wildcards fonctions-------------------------*/
void		check_for_wildcards(t_tree *cmd_node, t_stash *stash);
char		**build_new_argv(char **old_argv, char **matches, \
size_t arg_index, size_t matches_count);
void		cleanup_string_array(char **array);
void		sort_matches(char **matches, size_t count);
void		cleanup_matches(char **matches, size_t matches_count);
char		**find_matching_entries(const char *pattern, \
const char *pwd, size_t *matches_count);
bool		has_quoted_wildcard(const char *s);
bool		has_unquoted_wildcard(const char *s);
char		*remove_quotes(const char *s);
char		*get_working_directory(t_stash *stash);
void		resize_matches_if_needed(t_match_data *data);
void		process_directory_entries(DIR *dir, \
const char *pattern, t_match_data *data);
size_t		match_pattern(const char *pattern, const char *string);
size_t		handle_wildcards(t_tree *cmd_node, const char *pattern, \
size_t arg_index, const char *pwd);
size_t		process_no_wildcard(t_tree *cmd_node, size_t i);
size_t		process_quoted_wildcard(t_tree *cmd_node, size_t i);
size_t		process_unquoted_wildcard(t_tree *cmd_node, size_t i, char *pwd);

/*-----------------------Environment fonctions------------------------*/
void		swap_env(t_env *a, t_env *b);
char		**get_env_arr(t_env *env_list);
void		sort_env_list(t_env **env_list);
void		add_node(t_env **env_list, char *argv);
char		*add_env_value(char *key, t_stash *stash);
char		*get_env_value(t_env **env_list, char *key);
void		add_value(t_env **env_list, char *argv, char *key);
void		build_env(t_env **env_list, char **envp, t_stash *stash);
void		add_env_var(t_env **env_list, char *key, t_stash *stash);
void		check_existing_vars(t_env *env_list, char **keys, int *found);
void		update_env(t_env **env_list, char *argv, char *key, int start);

/*-------------------------Builtins fonctions-------------------------*/
int			echo(char **cmd);
int			pwd(t_stash *stash);
int			is_parent_builtin(char *cmd);
void		run_exit(char **cmd, t_stash *stash);
int			count_leading_dotdots(const char *path);
char		*handle_dotdots(char *new_path, int dotdots);
int			handle_argument(t_env **env_list, char *cmd);
int			env(t_env *env_list, t_stash *stash, char **cmd);
int			cd(char **cmd, t_env **env_list, t_stash *stash);
char		*handle_component_case(int dotdots, t_stash *stash);
int			unset(t_env **env_list, char **cmd, t_stash *stash);
int			export(char **cmd, t_env **env_list, t_stash *stash);
int			check_validity(char	*argv, char *initial, char *cmd);
void		refresh_pwd(t_env **env_list, t_stash *stash, char *cmd);
char		*handle_component(char *new_path, const char *component);
char		*get_next_component(const char *path, int *start, int *end);
int			run_builtins(char **cmd, t_env **env_list, int status, \
t_stash *stash);
char		*process_components(const char *path, int dotdots, \
t_stash *stash, char *component);
char		*expand_vars(char **old_cmd, t_env **env, int stash_status);
/*--------------------Garbage collector fonctions---------------------*/
void		*nalloc(size_t __size);
void		free_all_tracked(void);
t_gcnode	**memory_tracker(void);

/*------------------------------Utilities-----------------------------*/
void		close_fd(void);
char		*na_itoa(int n);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isspace(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			na_arrlen(char **arr);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);
long		na_atoi(const char *str);
char		*na_strdup(const char *s);
int			ft_str_isspace(char *str);
char		*ft_strdup(const char *s1);
int			ft_strcmp(char *s1, char *s2);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
char		*ft_strchr(const char *s, int c);
char		**na_split(char const *s, char c);
char		*ft_strrchr(const char *s, int c);
int			ft_isallchar(const char *str, char c);
void		*na_calloc(size_t count, size_t size);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memset(void *b, int c, size_t len);
int			na_mkstemp(char *template, t_redir *redir);
char		*na_strjoin(char const *s1, char const *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*na_substr(char const *s, unsigned int start, size_t len);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*get_next_line(int fd);

/*----------------------Redirections && heredoc-----------------------*/
int			handle_redirs(t_redir *redir, t_stash *stash);
void		manage_heredocs(t_tree *ast, t_stash *stash);
int			open_heredocs(t_redir *redir, t_stash *stash);
void		check_heredoc_limit(t_shell *shell, t_tree *ast);

/*------------------------------Events--------------------------------*/
void		display_intro(void);
void		is_it_dir(char *cmd);
void		errno_manager(char *cmd);
int			puterror(int program, char *cmd, char *arg, char *error);

/*-------------------------execute fonctions--------------------------*/
char		**get_path_list(char **env);
void		handle_special_cases(char **path_list, char **cmd);
int			execute_ast(t_tree *ast, t_env **env, t_stash *stash);
int			execute_pipe(t_tree *ast, t_env **env_list, t_stash *stash);
int			execute_parentheses(t_tree *ast, t_env **env, t_stash *stash, \
t_redir *redir);
int			execute_command(char **cmd, t_redir *redirs, t_env **env_list, \
t_stash *stash);
int			count_required_forks(t_tree *ast);
int			perform_dry_run_fork_test(int required_forks, t_stash *stash);
/*------------------------------signals-------------------------------*/
void		restore_terminal(t_stash *stash);
void		disable_echoctl(t_stash *stash);
void		handle_sigint_heredoc(int sig);
void		handle_sigint_prompt(int sig);
void		setup_signals_heredoc(void);
void		setup_signals_prompt(void);

/*---------------------Parsing STUFF------------------------------------------*/
int			init_shell(t_shell *shell);
int			lexer(t_shell *shell);
int			token_lexer(char *str);
int			skip_spaces(char *str);
int			parser(t_shell *shell);
int			operator_len(char *str);
int			ft_syntax_analyzer(char *str);
t_token		*new_token(char *value, int type);
void		parentheses_lexer(t_token **head);
int			handle_parentheses(t_shell *shell);
void		advanced_token_lexer(t_token **head);
int			parentheses_counter_v2(t_token *head);
int			handle_quotes(char *str, char quote_type);
void		link_token(t_token **head, t_token *node);
int			is_in_quotes(char *str);

/*-----------Tree Stuff-------------------*/
t_tree		*create_block(t_token **head, int count, int type);
void		create_pseudotree(t_tree **ast, t_token **tokens);
void		create_one_tree(t_tree **ast, t_token **tokens);
void		create_subtree(t_tree **ast, t_token **tokens);
void		link_redir(t_redir **list, t_redir *new_redir);
t_tree		*allocate_tree_node(int type, int cmd_count);
t_redir		*redir_list_maker(t_token **head);
t_tree		*create_p_block(t_token **head);
int			block_identifier(t_token *head);
t_token		*last_rp_token(t_token **head);
void		refresh_tokens(t_token **head);
t_token		*find_first_lp(t_token *head);
int			count_cmd_args(t_token *head);
t_redir		*redir_maker(t_token **data);
t_token		*find_and_or(t_token *head);
t_token		*find_pipe(t_token *head);
int			token_lookup(char *line);
int			count_chars(char *str);
	/*---------------------Checkers-------------------*/
char		ft_isquote(char c);
int			ft_is_redir(char *c);
int			ft_is_operator(char *c);
int			ft_isparentheses(char *c);
int			redir_identifier(char *str);
int			ft_syntax_err(t_shell *shell);
int			check_successor(t_token *head);
int			ft_is_bonus_operator(char *str);
int			check_predecessor(t_token *head);
int			simple_syntax_err(t_shell *shell);
int			advanced_syntax_err(t_shell *shell);

/*-----------Expand-----------------*/
void		expand_keys(t_var **keys, t_env **env, int stash_status, \
int *total_len);
char		*find_a_key(char *origin, int *quote, int *key_len, int *pos);
void		expand_redirs(t_redir **head, t_env **env, int stash_status);
void		expand_a_key(t_var *current, t_env **env, int stash_status);
void		update_cmd(char *origin, t_var **keys, char **destination);
void		expand_cmd(t_tree *ast, t_env **env, int stash_status);
void		filter_empty_nodes(t_token **head, size_t *argc);
void		check_quote(char *start, char *end, int *quote);
t_var		*create_key(char *origin, int *quote, int *pos);
char		**rebuild_cmd(t_token **list, size_t argc);
void		ft_copy_keys(char **dest, t_var *current);
void		store_args(t_token **list, char **origin);
void		find_all_keys(char *str, t_var **keys);
int			skip_quoted_str(char *str, char quote);
void		link_nodes(t_var **head, t_var *node);
int			in_quote_len(char *str, char quote);
int			multi_str_included(char *new_cmd);
void		expand_heredoc(t_redir **head);
int			expand_quotes(char **old_cmd);
int			is_empty_values(t_var *keys);
void		inject_quotes(char **str);
void		unmask_quotes(char *str);
int			is_valid_key(char key);
void		mask_quotes(char *str);
int			value_scan(char *arg);
int			key_scan(char *arg);
/*-----------free-------------*/
void		free_cmd(char **cmd);
void		free_tree(t_tree **ast);
void		free_keys(t_var **head);
void		free_tokens(t_token **head);
void		clear_memory(t_shell *shell);
/*-----------utilities-------------*/
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		ft_putendl_fd(char *s, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
char		*ft_strdup(const char *s1);
int			ft_str_isspace(char *str);
char		**ft_split_args(char *s);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isspace(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
char		*ft_itoa(int n);
	// ! REMOVE THS LATER
void		print_tokens(t_var **head);
void		print_redirs(t_redir *redir);
void		print_tree(t_tree *tree);
/*-- -- -- -- -- -- -- -Tree Visualization Functions-- -- -- -- -- -- -*/

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
void		visualize_ast_tree(t_tree *root);
void		visualize_tokens(t_token *head);

#endif

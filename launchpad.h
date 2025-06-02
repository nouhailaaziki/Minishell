/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchpad.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 10:54:18 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/02 14:06:32 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCHPAD_H
# define LAUNCHPAD_H

/*---------------------Header inclusion directive---------------------*/
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

/*-----------------------Format and Color Macros----------------------*/
# define BOLD "\033[1m"
# define RESET "\x1b[0m"
# define ORANGE "\x1b[38;5;214m"
# define PINK "\x1b[95m"

/*-----------------------The kind of each token-----------------------*/
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_REDIR,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_PAREN_LEFT,
	TOKEN_PAREN_RIGHT,
	TOKEN_EOF,
	TOKEN_INVALID
}	t_token_type;

/*--------------------Linked list of parsed tokens--------------------*/
typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

/*-----------------------Redirection type enum------------------------*/
typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_NONE
}	t_redir_type;

/*--------------------Redirection info for a command------------------*/
typedef struct s_redir
{
	size_t				index;
	t_redir_type		type;
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
	t_redir				*redirs;
	t_redir				*redirs_before;
	t_redir				*redirs_after;
	int					is_ambiguous;
	struct s_tree		*left;
	struct s_tree		*right;
}	t_tree;

// /*--------------------------Storage structure-------------------------*/
// typedef struct s_oyster
// {
// 	char			*pwd;
// 	t_env			*env;
// 	t_tree			*tree;
// 	t_path			*paths;
// 	t_redir			*redir;
// 	t_node_type		*node_type;
// 	struct s_oyster	*next;
// }	t_oyster;

void executor(t_tree *ast, t_env **env);

/*-------------------------parsing fonctions--------------------------*/
t_token *lexer(const char *input);
void 	free_tokens(t_token *tokens);
t_tree 	*parse_input(t_token **tokens);

/*-----------------------Environment fonctions------------------------*/
t_env	*env_node(char *envp);
void	upp_shlvl(t_env *node, int nbr);
void	build_env(t_env **env_list, char **envp);

/*-------------------------Builtins fonctions-------------------------*/
int		pwd(void);
int		echo(char **cmd);
int		env(t_env *env_list);
int		cd(char **cmd, t_env **env_list);
int		unset(t_env **env_list, char **cmd);
int		export(char **cmd, t_env **env_list);
void	run_exit(char **cmd, int exit_status);
void	handle_argument(t_env **env_list, char *cmd);
t_env	*create_node(char *argv, size_t key_len, char *sign);
void	sort_env_list(t_env **env_list);
int		check_validity(char	*argv, char *cmd);
void	add_value(t_env	**env_list, char *argv, char *key);
void	update_env(t_env **env_list, char *argv, char *key, int start);
void	ft_putstr_fd(char *s, int fd);

/*--------------------Garbage collector fonctions---------------------*/
void		*nalloc(size_t __size);
void		free_all_tracked(void);
t_gcnode	**memory_tracker(void);

/*-------------------Utilities from libft (Updated)-------------------*/
char	*na_itoa(int n);
int		ft_isdigit(int c);
int		ft_arrlen(char **arr);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
char	*na_strdup(const char *s);
long	strict_atoi(const char *str);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	**na_split(char const *s, char c);
int		ft_isallchar(const char *str, char c);
void	*na_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
char	*na_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*na_substr(char const *s, unsigned int start, size_t len);
/*----------------------------------Events-----------------------------------*/
void	puterror_to_exit(char *cmd, char *error, int ex);

#endif
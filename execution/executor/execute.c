/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:12 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/05 15:15:52 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

// pid_t my_pid;
// // 1. Check if standard input (file descriptor 0) is a terminal.
// // This is good practice to ensure the ioctl call will succeed
// // 2. Use ioctl to get the foreground process group ID from the terminal.
// //    - STDIN_FILENO (0): The file descriptor for the terminal.
// //    - TIOCGPGRP: The request to get the terminal's foreground process group.
// //    - &my_pid: A pointer to a pid_t variable where the result will be stored.
// //
// // For a simple program, the Process ID is the same as the Process Group ID.
// if (ioctl(STDIN_FILENO, TIOCGPGRP, &my_pid) == -1)
// {
// 	// perror() is on the allowed list.
// 	perror("ioctl");
// 	exit(1);
// }
// // 3. Print the result.
// printf("My PID (retrieved via ioctl) is: %d\n", my_pid);


int	is_valid_key(char *key)
{
	if(key && !ft_isalnum(key[1]) && key[1] != '_' && key[1] != '?')
		return (0);
	return (1);
}


char * is_valid_expand(t_env **env,char *origin)
{
	char	*dollar;
	int		i;
	char	*value;
	char	*buffer;
	char 	*key;
	if(!origin)
		return (0);
	i = 0;
	dollar = ft_strchr(origin, '$');
	if(!dollar || !++dollar || !is_valid_key(dollar) ) //leak warning idk
		return (origin);
	while(origin[i] && origin[i] != '$')
		i++;
	// key = extract_key(dollar);
	value = get_env_value(env, key);
	if(!value)
		return (free(origin),ft_strdup(""));
	buffer = ft_strjoin(buffer,value);
	free(origin);
	return (na_strdup(value));
}
// char *expand_word(t_env **env, char *origin)
// {
// 	// char	*dollar;
// 	// int		start;
// 	// char	*value;
// 	// char	*buffer;
// 	// char	*key;
// 	// if (!origin || !env)
// 	// 	return (0);
// 	// start = 0;
// 	// dollar = ft_strchr(origin, '$');
// 	// if(!dollar || dollar[0] + 1 != '\0' )
// 	// 	return (origin);
// 	// while(dollar)
// 	// {
// 	// 	if (in_s_quotes(origin, start)	|| !is_valid_key(dollar + 1) )
// 	// 		start= dollar++;
// 	// 	dollar = ft_strchr(dollar, '$');
// 	// }
// }

int in_s_quotes(char *origin, int start)
{
	int	in_s_quote;
	int	i;

	in_s_quote = 0;
	i = 0;
	while (origin[i] && i < start )
	{
		if (origin[i] == '\'')
			in_s_quote = !in_s_quote;
		i++;
	}
	if(in_s_quote)
		return (1);
	return (0);
}
void check_quote(char *str, char *end, int *quote)
{
	printf("[%s][%s]\n", str, end);
	while (str != end)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (*quote == 0)
				*quote = *str;
			else if (*quote == *str)
				*quote = 0;//"'"
		}
		str++;
	}
}

t_var *find_a_key(char *origin, int *quote)
{
	int		i;
	char	*dollar;
	t_var	*key;

	1 && (i = 0, dollar = ft_strchr(origin,'$'));
	if(!dollar || !is_valid_key(dollar) )
		return (printf("no more keys here\n"), NULL);
	key = ft_calloc(1, sizeof(t_var));
	if(!key)
		return NULL;
	check_quote(origin, dollar, quote);
	printf("-----------%c\n", *quote);
	if(dollar[i+1] == '?')
	{
		key->len = 2;
		key->key = ft_strdup("$?");
		key->expandable = *quote;
		return (key);
	}
	i++;
	while (dollar[i] && ft_isalnum(dollar[i]))
		i++;
	key->len = i;
	key->key = ft_substr(dollar, 0,i);
	key->expandable = *quote; //!in_s_quotes(origin, i);
	if(!key)
		return (NULL);
	return (key);
}
void	link_nodes(t_var **head, t_var *node)
{
	t_var	*tmp;

	if (!node)
	{
		ft_putendl_fd("Error Node is Empty\n", 2);
		return ;
	}
	if (!head || !*head)
	{
		*head = node;
		node->next = NULL;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->next = NULL;
}
void find_all_keys(char *str, t_var **keys,int stash_status)
{
	int i;
	int	key_len;
	t_var *key;
	int quote;

	quote = 0;
	i = 0;
	key_len = 0;
	while(str[i])
	{
		// check_quote(str, str + i, &quote);
		key = find_a_key(&str[i], &quote);
		if(!key)
			break;
		link_nodes(keys, key);
		i += key->len + 1;
	}
}

int expand_keys(t_var **head, t_env **env, int stash_status)
{
	t_var * current;
	char *value;
	int len;

	len = 0;
	current = *head;
	while(current)
	{
		if(current->expandable != '\'')
		{
			value = get_env_value(env, &(current->key[1]));
			free(current->key);
			current->key = value;
			current->len = ft_strlen(current->key);
			len += current->len;
		}
		else
			len += current->len;
		current = current->next;
	}
	print_tokens(head);
	return len;
}



void expand_cmd(char** cmd, t_env **env, int stash_status)
{
	int i;
	int len;
	t_var *keys;
	char *new_cmd;

	if(!cmd || !*cmd)
		return ;
	i = 0;
	keys = NULL;
	find_all_keys(cmd[i], &keys, stash_status);
	len = expand_keys(&keys, env , stash_status);
	new_cmd = ft_calloc(ft_strlen(cmd[0]) + len, sizeof(char));
	if(!new_cmd)
		return;

}





int	execute_ast(t_tree *ast, t_env **env, t_stash *stash)
{
	if (!ast)
		return (stash->status);
	if (ast->type == NODE_COMMAND){
		expand_cmd(ast->cmd, env, stash->status);
		stash->status = execute_command(ast->cmd, ast->redirs, env, stash);
	}
	else if (ast->type == NODE_PIPE)
		stash->status = execute_pipe(ast, env, stash);
	else if (ast->type == NODE_AND)
	{
		stash->status = execute_ast(ast->left, env, stash);
		if (stash->status == 0)
			stash->status = execute_ast(ast->right, env, stash);
	}
	else if (ast->type == NODE_OR)
	{
		stash->status = execute_ast(ast->left, env, stash);
		if (stash->status != 0)
			stash->status = execute_ast(ast->right, env, stash);
	}
	else if (ast->type == NODE_PARENTHESES)
		stash->status = execute_parentheses(ast, env, stash, ast->redirs);
	return (stash->status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:12 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/04 14:50:45 by yrhandou         ###   ########.fr       */
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

int in_s_quotes(char *origin, int start)
{
	int in_s_quote;

	in_s_quote = 0;
	while (origin[start] && origin[start] != '$')
	{
		if (origin[start] == '\'' && !in_s_quote)
			in_s_quote += 1;
		else if (origin[start] == '\'' && !in_s_quote)
			in_s_quote -= 1;
		start++;
	}
	if(in_s_quote)
		return (1);
	return (0);
}

int	is_valid_key(char *key)
{
	if((!ft_isalnum(key[0]) && key[0] != '_' && key[0] != '?'))
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
	if(!dollar || !++dollar || in_s_quotes(origin,0 ) || !is_valid_key(dollar) ) //leak warning idk
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

t_var *find_a_key(char *origin , int stash_status)
{
	int		i;
	char	*dollar;
	t_var	*key;

	dollar = ft_strchr(origin,'$');
	if(!dollar || !is_valid_key(&dollar[1]) )
		return (printf("no key here\n"), NULL);
	if(in_s_quotes(origin, dollar - origin))
	{
		printf("hey %s\n", dollar - origin);
		exit(1);
	}
	key = ft_calloc(1, sizeof(t_var));
	if(!key)
		return NULL;
	i = 0;
	if(++dollar && dollar[i] == '?')
	{
		key->len = 1;
		key->key = ft_itoa(stash_status);
		printf("key is %s\n with len %d \n", key->key, key->len);
		return (key);
	}
	while (dollar[i] && ft_isalnum(dollar[i]))
		i++;
	key->len = i;
	key->key = ft_substr(dollar, 0,i);
	if(!key)
		return (NULL);
	printf("key is %s with len %d \n", key->key, key->len);
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
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	tmp->next = node;
	node->next = NULL;
}
void find_all_keys(char *str, int stash_status)
{
	int i;
	t_var **var;
	t_var *key;
	i = 0;
	while(str[i])
	{
		key = find_a_key(&str[i], stash_status);
		if(!var)
			return;
		link_nodes(var, key); // you stopped here
		i += key->len + 1;
	}
}


void expand_cmd(char** cmd, t_env **env, int stash_status)
{
	int i;
	size_t len;

	i = 0;
	len = 0;
	while(cmd[i])
	{
		// find_key(cmd[i], stash_status );
		find_all_keys(cmd[i], stash_status);
		i++;
	}
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

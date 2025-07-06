/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:12 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/06 17:24:42 by yrhandou         ###   ########.fr       */
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

// int in_s_quotes(char *origin, int start)
// {
// 	int	in_s_quote;
// 	int	i;

// 	in_s_quote = 0;
// 	i = 0;
// 	while (origin[i] && i < start )
// 	{
// 		if (origin[i] == '\'')
// 			in_s_quote = !in_s_quote;
// 		i++;
// 	}
// 	if(in_s_quote)
// 		return (1);
// 	return (0);
// }
// void check_quote(char *str, char *end, int *quote)
// {
// 	printf("[%s][%s]\n", str, end);
// 	while (str != end)
// 	{
// 		if (*str == '\'' || *str == '\"')
// 		{
// 			if (*quote == 0)
// 				*quote = *str;
// 			else if (*quote == *str)
// 				*quote = 0;//"'"
// 		}
// 		str++;
// 	}
// }


int	is_valid_key(char *key)
{
	if(key && ( key[1] == '?' || key[1] == '$' || key[1] == '_' || ft_isalnum(key[1])))
		return (1);
	return (0);
}

void check_quote(char *start, char *end, int *quote)
{
	int i;

	i = 0;
	while (start != end)
	{
		if(*start == '"' || *start =='\'')
		{
			if(*quote == 0)
				*quote = *start;
			else if( *quote == *start)
				*quote = 0;
		}
		start++;
	}

}


char *find_a_key(char *origin, int *quote , int *key_len ,int *pos)
{
	int		i;
	char	*dollar;

	i = 0;
	while(origin[i] && origin[i] != '$')
		i++;
	if(!origin[i] || !is_valid_key(&origin[i]) )
		return (NULL);
	check_quote(origin, &origin[i], quote);
	dollar = &origin[i];
	*pos += i;
	i = 1;
	while (dollar[i] && (ft_isalnum(dollar[i]) || dollar[i] == '_'))
		i++;
	dollar = ft_substr(dollar, 0,i);
	if(!dollar)
		return (NULL);
	*key_len = i;
	*pos += i;
	return (dollar);
}



t_var *create_key(char *origin, int *quote , int *pos)
{
	char	*dollar;
	t_var	*key;
	int key_len;

	dollar = find_a_key(origin, quote ,&key_len , pos);
	if(!dollar)
		return (printf("no key found\n"), NULL);
	key = ft_calloc(1, sizeof(t_var));
	if(!key)
		return NULL;
	if(dollar[1] == '?' || dollar[1] == '$') // * you should correct this
	{
		key->key = ft_substr(dollar,0,2);
		key->key_len = 2;
		key->expandable = *quote;
		return (key);
	}
	key->key = dollar;
	key->key_len = ft_strlen(dollar);
	key->expandable = *quote;
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
	int pos;
	int	key_len;
	t_var *key;
	int quote;

	quote = 0;
	pos = 0;
	while(str[pos])
	{
		key = create_key(&str[pos], &quote, &pos);
		if(!key)
			break;
		link_nodes(keys, key);
	}
}

int expand_keys(t_var **head, t_env **env, int stash_status , int *keys_len)
{
	t_var	*current;
	char	*value;
	int		value_len;

	value_len = 0;
	current = *head;
	while(current)
	{
		*keys_len += current->key_len ;
		if(current->expandable != '\'')
		{
			value = get_env_value(env, &(current->key[1]));
			if(!ft_strncmp(current->key, "$?", 2))
				current->value = ft_itoa(stash_status);
			else
				current->value = ft_strdup(value);
			current->value_len = ft_strlen(current->value);
			value_len += current->value_len;
		}
		current = current->next;
	}
	print_tokens(head);
	return value_len;
}

void update_cmd(char *origin ,t_var *keys, char **destination)
{
	t_var *current_key;
	char *dest;

	1 && (dest = *destination,	current_key = keys);
	while(*origin)
	{
		if(*origin != '$')
		{
			*dest++ = *origin++;
			continue ;
		}
		if(*origin && !ft_strncmp(origin, current_key->key, current_key->key_len))
		{
			if(current_key->expandable != '\'')
			{
				ft_memcpy(dest, current_key->value, current_key->value_len);
				dest += current_key->value_len;
			}
			else
			{
				ft_memcpy(dest, current_key->key, current_key->key_len);
				dest += current_key->key_len;
			}
			origin += current_key->key_len;
			current_key = current_key->next;
		}
	}
	*dest = '\0';
}


void expand_cmd(char **cmd, t_env **env, int stash_status)
{
	int i;
	int value_len;
	int keys_len;
	t_var *keys;
	char *new_cmd;

	if(!cmd || !*cmd )
		return ;
	i = 0;
	keys_len = 0;
	while (cmd[i])
	{
		keys = NULL;
		find_all_keys(cmd[i], &keys, stash_status);
		if(!keys)
		{
			i++;
			continue;
		}
		value_len = expand_keys(&keys, env , stash_status , &keys_len);
		new_cmd = ft_calloc(ft_strlen(cmd[i]) + value_len - keys_len, sizeof(char));
		if(!new_cmd)
			return;
		update_cmd(cmd[i], keys, &new_cmd);
		free(cmd[i]);
		cmd[i] = new_cmd;
		free_keys(&keys);
		printf("new cmd : %s\n",	cmd[i]);
		i++;
	}
}
		// printf("CMD length : %zu\n",ft_strlen(cmd[0]));
		// printf("Values length : %d\n",value_len);
		// printf("Keys length : %d\n",keys_len);







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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:12 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/02 18:35:42 by yrhandou         ###   ########.fr       */
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
	if((!ft_isalnum(key[0]) && key[0] != '_'))
		return (0);
	return (1);
}

char *extract_key(char *dollar)
{
	int		i;
	char	*key;

	i = 0;
	while(dollar[i] && ft_isalnum(dollar[i]))
		i++;
	key = ft_substr(dollar, 0, i);
	if(!key)
		return (NULL);
	return (key);
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
	key = extract_key(dollar);
	value = get_env_value(env, key);
	if(!value)
		return (free(origin),ft_strdup(""));
	buffer = ft_strjoin(buffer,value);
	free(origin);
	return (na_strdup(value));
}
char *expand_word(t_env **env, char *origin)
{
	char	*dollar;
	int		start;
	char	*value;
	char	*buffer;
	char	*key;

	if (!origin || !env)
		return (0);
	start = 0;
	dollar = ft_strchr(origin, '$');
	if(!dollar || dollar[0] + 1 != '\0' )
		return (origin);
	while(dollar)
	{
		//? can i swap the dollar and restore it later to mark it passed through / or pointer arithmetic is better.
		if (in_s_quotes(origin, start)	|| !is_valid_key(dollar + 1) )
			start= dollar++;
		else
		{
			key = extract_key(++dollar);
			value = get_env_value(env, key);
			if (!value)
			{
				puts("I should clear the key from the string");
				return NULL;
			}
			else
			{
				puts("inject the key's value");
			}

		}
		dollar = ft_strchr(dollar, '$');
	}
}
char **split_quotes(char *origin)
{
	int i;
	char commander;
	int in_quote;

	if(!origin || !ft_strchr(origin, '"' )|| !ft_strchr(origin, '\''))
		return NULL;
	i = 0;
	commander = 0;
	// if(origin[i] == '"' || origin[i] == '\'')
	// 	commander = origin[i++];
	while(origin[i] && )
	{
		if(origin[i] == commander)
			break;
		i++;
	}
	printf("substr len : %d", i);

}



void expand_cmd(char** cmd, t_env **env)
{
	int i;
	int j;
	if (!cmd || !*cmd)
		return;
	i = 0;
	// if(!ft_strcmp(cmd[i],"export"))
	// {
	// 	printf("MISSING EXPORT HANDLING\n");
	// 	return ;
	// }
	while(cmd[i])
	{
		cmd[i] = expand_word(env, cmd[i]);
		i++;
	}
}





int	execute_ast(t_tree *ast, t_env **env, t_stash *stash)
{
	if (!ast)
		return (stash->status);
	if (ast->type == NODE_COMMAND){
		expand_cmd(ast->cmd, env);
		// printf("%s\n",ast->cmd[0]);
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

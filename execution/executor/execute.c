/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:12 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/08 11:45:02 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"


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
int	execute_ast(t_tree *ast, t_env **env, t_stash *stash)
{
	if (!ast)
		return (stash->status);
	if (ast->type == NODE_COMMAND)
  {
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

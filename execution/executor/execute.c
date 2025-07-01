/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:12 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/01 17:19:35 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

char * is_valid_expand(t_env **env,char *word)
{
	char	*dollar;
	int i;
	int s_quote;
	char *value;


	if(!word)
		return (0);
	i = 0;
	dollar = ft_strchr(word, '$');
	if(!dollar || !++dollar)
		return word[0];
	value = get_env_value(env,dollar);
	if(!value)
		return word;
	return (value);
	// while(cmd[i] != '$')
	// 	i++;


	// if(str[i] == '\'' || str[i] == '"')
	// 	commander = str[i];
	// while(str[i])
	// {
	// 	i++;
	// }
}


void expand_cmd(char** cmd, t_env **env)
{
	int i;
	int j;
	if(!cmd || !*cmd)
		return;
	i = 0;
	j = 0;
	if(!ft_strcmp(cmd[i],"export"))
	{
		printf("MISSING EXPORT HANDLING\n");
		return ;
	}
	while(cmd[i])
	{
		cmd[i] = is_valid_expand(env, cmd[i]);
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

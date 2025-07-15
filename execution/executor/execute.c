/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:12 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/15 19:45:43 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void unmask_quotes(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(str[i] == 3 || str[i] == 4)
		{
			if (str[i] == 3)
				str[i] = '\'';
			else
				str[i] = '"';
		}
		i++;
	}
}
int is_in_quotes(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote =ft_isquote(str[i]);
	if(!ft_isquote(str[i]))
		return (0);
	while (str[i] && str[i] != quote)
		i++;
	if(str[i] == quote)
		return (1);
	return (0);

}
int value_scan(char *arg)
{
	int		i;
	char	*value;

	i = 0;
	value = ft_strchr(arg,'=');
	if(!value || !++value)
		return 0;
	if(is_in_quotes(arg))
		return 0;
	return 1;
}

int key_scan(char *arg)
{
	int	i;

	i = 0;
	if(!arg)
		return 0;
	if(ft_strchr(arg, '\'') || ft_strchr(arg, '\"'))
		return 0;
	while(arg[i] && arg[i] != '=')
	{
		// if(is_valid_key(arg[i]))
		// 	return 0;
		i++;
	}
	return (1);
}

void inject_quotes(char **str)
{

	char *value;
	char *new_value;
	char *tmp;

	value = ft_strchr(*str, '=');
	if(!value|| !++value)
		return ;
	new_value = ft_calloc(sizeof(char),ft_strlen(value) + 2);
	if(!new_value)
		return ;
	tmp = new_value;
	new_value[0] = '"';
	new_value  = ft_strjoin(new_value, *str);
	free(tmp);
	new_value[ft_strlen(*str)+1] = '\"';
	free(*str);
	*str = new_value;
}

void	expand_export(t_tree *ast, t_env **env, int stash_status)
{
	int		i;
	char	**current;

	current = ast->cmd;
	if (!current || !*current || !**current)
		return ;
	if(ft_strcmp(ast->cmd[0], "export"))
		return ;
	i = 1;
	while (current && current[i])
	{
		if(!key_scan(ast->cmd[i]) || !value_scan(ast->cmd[i]))
		{
			i++;
			continue;
		}
		current[i] = expand_vars(&current[i], env, stash_status);
		inject_quotes(&current[i]);
		i++;
	}
}

void	expand_all(t_tree *ast, t_env **env, t_stash *stash)
{
	int	i;

	expand_export(ast, env, stash->status);
	expand_cmd(ast, env, stash->status);
	expand_redirs(&ast->redirs, env, stash->status);
	check_for_wildcards(ast, stash);
	i = 0;
	while(ast->cmd && ast->cmd[i])
		expand_quotes(&ast->cmd[i++]);
	i = 0;
	while(ast->cmd && ast->cmd[i])
		unmask_quotes(ast->cmd[i++]);
}


int	execute_ast(t_tree *ast, t_env **env, t_stash *stash)
{
	if (!ast)
		return (stash->status);
	if (ast->type == NODE_COMMAND)
	{
		expand_all(ast, env, stash);
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

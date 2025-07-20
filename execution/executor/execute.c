/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:12 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/20 13:32:59 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	expand_export(t_tree *ast, t_env **env, int stash_status)
{
	int		i;
	char	**current;

	current = ast->cmd;
	if (!current || !*current || !**current)
		return ;
	if (ft_strcmp(ast->cmd[0], "export"))
		return ;
	i = 1;
	while (current && current[i])
	{
		if (!key_scan(ast->cmd[i]) || !value_scan(ast->cmd[i]))
		{
			i++;
			continue ;
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
	// while (ast->cmd && ast->cmd[i])
	// 	expand_quotes(&ast->cmd[i++]);
	i = 0;
	while (ast->cmd && ast->cmd[i])
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

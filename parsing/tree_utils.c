/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:39:28 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/29 09:52:26 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

void	refresh_tokens(t_token **tokens)
{
	t_token	*current;

	current = *tokens;
	while (current && current->prev && current->prev->position != -1)
		current = current->prev;
	*tokens = current;
}

t_tree	*allocate_tree_node(int type, int cmd_count)
{
	t_tree	*head;

	head = ft_calloc(1, sizeof(t_tree));
	head->cmd = NULL;
	if (!head)
		return (NULL);
	if (type == NODE_COMMAND)
	{
		head->cmd = ft_calloc(cmd_count + 1, sizeof(char **));
		head->argc = cmd_count;
	}
	else
	{
		head->cmd = NULL;
		head->argc = 0;
	}
	head->redirs = NULL;
	head->type = type;
	head->left = NULL;
	head->right = NULL;
	return (head);
}

int	block_identifier(t_token *head)
{
	if (head->type == TOKEN_OR)
		return (NODE_OR);
	else if (head->type == TOKEN_AND)
		return (NODE_AND);
	else if (head->type == TOKEN_PIPE)
		return (NODE_PIPE);
	else if (head->type == TOKEN_PAREN_LEFT)
		return (NODE_PARENTHESES);
	else
		return (NODE_COMMAND);
}

int	count_cmd_args(t_token *head)
{
	int	count;

	count = 0;
	while (head && head->position != -1)
	{
		if (head->type == TOKEN_PIPE || head->type == TOKEN_AND || \
			head->type == TOKEN_OR || head->type == TOKEN_PAREN_RIGHT)
			break ;
		else if (head->type == R_FILE || head->type == REDIR_IN || \
				head->type == REDIR_OUT || head->type == REDIR_APPEND || \
				head->type == REDIR_HEREDOC)
		{
			head = head->next;
			continue ;
		}
		count++;
		head = head->next;
	}
	return (count);
}

t_tree	*create_block(t_token **head, int count, int type)
{
	t_tree	*tree;
	int		i;
	t_token	*current;

	i = 0;
	tree = allocate_tree_node(type, count);
	if (!tree)
		return (NULL);
	tree->redirs = redir_list_maker(head);
	current = *head;
	if (current->type != TOKEN_CMD && current->type != TOKEN_ARG)
		count = 0;
	while (current && i < count)
	{
		if (current->type == TOKEN_CMD || current->type == TOKEN_ARG)
		{
			tree->cmd[i++] = ft_strdup(current->value);
			current->position = -1;
		}
		current = current->next;
	}
	if (tree->cmd)
		tree->cmd[i] = NULL;
	return (tree);
}

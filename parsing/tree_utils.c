/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:39:28 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/19 06:00:29 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

t_tree *create_tree_node(int type,int cmd_count)
{
	t_tree *head;

	head = ft_calloc(1, sizeof(t_tree));
	head->cmd = NULL;
	if (!head)
		return (NULL);
	if(cmd_count)
		head->cmd = ft_calloc(cmd_count +1,sizeof(char **));
	head->redirs = NULL;
	head->type = type;
	head->argc = cmd_count;
	head->left = NULL;
	head->right = NULL;
	return (head);
}

t_token *ft_token_search(t_token *head, int type)
{
	t_token	*current;

	current = head;
	while(current)
	{
		if(current->type == type)
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_redir *redir_maker(t_token **data)
{
	t_redir *redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if(!redir)
		return (NULL);
	redir->fd = -1;
	redir->flag = 0;
	if((*data)->next)
	{
		(*data)->position = -1;
		redir->file = ft_strdup((*data)->next->value);
		if(!redir->file)
			return printf("This is not supposed to happen.\n") ,NULL;
	}
	redir->index = 0;
	redir->type = (*data)->type;
	redir->next = (NULL);
	return (redir);
}

void link_redir(t_redir **list,t_redir *new_redir)
{
	t_redir *tmp;

	tmp = *list;
	if (!*list)
	{
		*list = new_redir;
		new_redir->next = NULL;
		new_redir->index = 0;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redir;
	new_redir->index = tmp->index + 1;
	new_redir->next = NULL;
}

int block_identifier(t_token *head)
{
	if (head->type == TOKEN_OR)
		return NODE_OR;
	else if (head->type == TOKEN_AND)
		return NODE_AND;
	else if (head->type == TOKEN_PIPE)
		return NODE_PIPE;
	else
		return NODE_COMMAND;
}
 /**
 * links the redirections nodes to a linked list
*/
t_redir *redir_list_maker(t_token **head)
{
	t_token *tmp;
	t_redir *redir_list;

	redir_list = NULL;
	if( !head ||!*head)
	{
		printf("This is not supposed to happen.\n");
		return (NULL);;
	}
	tmp = *head;
	while (tmp && tmp->type != TOKEN_AND && tmp->type != TOKEN_OR)
	{
		if (tmp->type > R_FILE)
		{
			link_redir(&redir_list, redir_maker(&tmp));
		}
		tmp = tmp->next;
	}
	return (redir_list);
}

int block_arg_counter(t_token *head)
{
	int count;

	count = 0;
	while (head && head->type)
	{
		if (head->type == TOKEN_AND || head->type == TOKEN_OR)
			break;
		else if (head->type >= R_FILE)
		{
			head = head->next;
			continue;
		}
		count++;
		head = head->next;
	}
	return (count);
}
int sub_block_arg_counter(t_token *head)
{
	int count;

	count = 0;
	while (head)
	{
		if (head->type == TOKEN_PIPE)
			break;
		else if (head->type >= R_FILE)
		{
			head = head->next;
			continue;
		}
		count++;
		head = head->next;
	}
	return (count);
}
t_tree *create_block(t_token **head, int count, int type)
{
	t_tree	*tree;
	int		i;
	t_token	*current;

	i = 0;
	tree = NULL;
	tree = create_tree_node(type, count);
	if (!tree)
		return NULL;
	tree->redirs = redir_list_maker(head);
	current = *head;
	while (current && i < count)
	{
		if (current->type < TOKEN_PAREN)
		{
			tree->cmd[i++] = ft_strdup(current->value);
		}
		current = current->next;
	}
	if(tree->cmd)
		tree->cmd[i] = NULL;
	return (tree);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:39:28 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/27 14:40:32 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

t_tree *allocate_tree_node(int type,int cmd_count)
{
	t_tree *head;

	head = ft_calloc(1, sizeof(t_tree));
	head->cmd = NULL;
	if (!head)
		return (NULL);
	if(type == NODE_COMMAND)
	{
		head->cmd = ft_calloc(cmd_count +1,sizeof(char **));
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

t_redir *redir_maker(t_token **data)
{
	t_redir *redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if(!redir)
		return (NULL);
	redir->fd = -1;
	redir->fd_RD = -1;
	redir->fd_WR = -1;
	redir->flag = 0;
	(*data)->position = -1;
	if((*data)->next)
	{
		redir->file = ft_strdup((*data)->next->value);
		(*data)->next->position = -1;
		if(!redir->file)
			return printf("This is not supposed to happen.\n") ,NULL;
	}
	redir->index = 0;
	redir->type = (*data)->type;
	redir->next = (NULL);
	return (redir);
}

void link_redir(t_redir **head,t_redir *new_redir)
{
	t_redir *tmp;

	tmp = *head;
	if (!*head)
	{
		*head = new_redir;
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
	else if (head->type == TOKEN_PAREN_LEFT)
		return NODE_PARENTHESES;
	else
		return NODE_COMMAND;
}
t_token *last_rp_token(t_token **head)
{
	t_token *current;
	t_token *last_rp_token;
	if (!head)
		return (printf("This is not supposed to happen\n"), NULL);
	current = *head;
	last_rp_token = NULL;
	while (current && current->next && current->next->position != -1)
	{
		if (current->type == TOKEN_PAREN_RIGHT)
			last_rp_token = current->next;
		current = current->next;
	}
	if(last_rp_token != NULL)
		last_rp_token->position = -1;
	return (last_rp_token);
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
	if((*head)->type == TOKEN_PAREN_LEFT)
		tmp = last_rp_token(head);
	while (tmp && tmp->type != TOKEN_AND && tmp->type != TOKEN_OR && tmp->type != TOKEN_PIPE && tmp->type != TOKEN_PAREN_LEFT && tmp->type != TOKEN_PAREN_RIGHT)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT || tmp->type == REDIR_APPEND || tmp->type == REDIR_HEREDOC)
		{
			link_redir(&redir_list, redir_maker(&tmp));
		}
		tmp = tmp->next;
	}
	return (redir_list);
}
int count_cmd_args(t_token *head)
{
	int count;

	count = 0;
	while (head && head->position != -1)
	{
		if (head->type == TOKEN_PIPE || head->type == TOKEN_AND || head->type == TOKEN_OR || head->type == TOKEN_PAREN_RIGHT)
			break;
		else if (head->type == R_FILE || head->type == REDIR_IN || head->type == REDIR_OUT || head->type == REDIR_APPEND || head->type == REDIR_HEREDOC)
		{
			head = head->next;
			continue;
		}
		count++;
		head = head->next;
	}
	return (count);
}

t_token	*get_reds(t_token *tok)
{
	int	expectations = 1;
	t_token	*curr  = tok->next;

	while (curr && expectations)
	{
		if (curr->type == TOKEN_PAREN_LEFT)
			expectations++;
		else if (curr->type == TOKEN_PAREN_RIGHT)
			expectations--;
		curr = curr->next;
	}
	return curr;
}

t_tree *expand_block(t_token *token)
{
	t_tree	*root = malloc(sizeof(t_tree));
	t_token	*block = NULL;
	t_token	*reds = NULL;
	if (!root)
		return (NULL);
	printf("here\n");
	ft_bzero(root, sizeof(t_tree));
	root->type = NODE_PARENTHESES;
	if (token->prev)
		token->prev->next = token->next;
	// free(token->value);
	// free(token);
	block = token->next;
	reds = get_reds(token);
	printf("%s\n", reds->value);
	if (reds->prev && reds->prev->prev)
		reds->prev->prev->next = NULL;
	// free(reds->prev->value);
	// free(reds->prev);
	root->left = create_tree(block);
	root->redirs = redir_list_maker(&reds);
	root->right = NULL;
	return (root);

}
t_tree *
create_p_block(t_token **head)
{
	t_tree *p_block;
	int i ;

	i =0;
	p_block = allocate_tree_node(NODE_PARENTHESES, 0);
	if(!p_block)
		return (NULL);
	p_block->redirs = redir_list_maker(head) ;
	return (p_block);
}
t_tree *create_block(t_token **head, int count, int type)
{
	t_tree	*tree;
	int		i;
	t_token	*current;

	i = 0;
	tree = allocate_tree_node(type, count);
	if (!tree)
		return NULL;
	tree->redirs = redir_list_maker(head);
	current = *head;
	if (current->type != TOKEN_WORD && current->type != TOKEN_ARG)
		count = 0;
	while (current && i < count)
		{
			if (current->type == TOKEN_WORD || current->type == TOKEN_ARG)
			{
				tree->cmd[i++] = ft_strdup(current->value);
				current->position = -1;
			}
			current = current->next;
		}
	if(tree->cmd)
		tree->cmd[i] = NULL;
	return (tree);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:39:28 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/24 17:47:39 by noaziki          ###   ########.fr       */
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
	while (tmp && tmp->type != TOKEN_AND && tmp->type != TOKEN_OR && tmp->type != TOKEN_PIPE)
	{
		if (tmp->type > R_FILE)
		{
			link_redir(&redir_list, redir_maker(&tmp));
		}
		tmp = tmp->next;
	}
	return (redir_list);
}
int sub_block_arg_counter(t_token *head)
{
	int count;

	count = 0;
	while (head)
	{
		if (head->type == TOKEN_PIPE || head->type == TOKEN_AND || head->type == TOKEN_OR)
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
		if (current->type < TOKEN_PAREN )
		{
			tree->cmd[i++] = ft_strdup(current->value);
		}
		current = current->next;
	}
	if(tree->cmd)
		tree->cmd[i] = NULL;
	return (tree);
}

// ANSI color codes
#define ANSI_RESET "\033[0m"
#define ANSI_CYAN "\033[36m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_GREEN "\033[32m"
#define ANSI_MAGENTA "\033[35m"
#define ANSI_RED "\033[31m"

// Get node type string
const char *get_node_type_str(t_node_type type)
{
	switch (type)
	{
	case NODE_COMMAND:
		return ANSI_CYAN "CMD" ANSI_RESET;
	case NODE_PIPE:
		return ANSI_YELLOW "PIPE" ANSI_RESET;
	case NODE_OR:
		return ANSI_YELLOW "||" ANSI_RESET;
	case NODE_AND:
		return ANSI_YELLOW "&&" ANSI_RESET;
	case NODE_PARENTHESES:
		return ANSI_CYAN "()" ANSI_RESET;
	default:
		return ANSI_RED "UNKNOWN" ANSI_RESET;
	}
}

// Get redirection type string
const char *get_redir_type_str(t_token_type type)
{
	switch (type)
	{
	case REDIR_IN:
		return ANSI_MAGENTA "< (REDIR_IN)" ANSI_RESET;
	case REDIR_OUT:
		return ANSI_MAGENTA "> (REDIR_OUT)" ANSI_RESET;
	case REDIR_APPEND:
		return ANSI_MAGENTA ">> (REDIR_APPEND)" ANSI_RESET;
	case REDIR_HEREDOC:
		return ANSI_MAGENTA "<< (REDIR_HEREDOC)" ANSI_RESET;
	default:
		return ANSI_RED "Unknown (REDIR_NONE)" ANSI_RESET;
	}
}

// Print command, parentheses, and redirection details for a node
void print_node_details(t_tree *node, char *prefix, int is_last)
{
	if (node->type == NODE_COMMAND)
	{
		// Print command node header
		printf("%s%s %sCommand Node: %u%s\n", prefix, is_last ? "└──" : "├──",
			   ANSI_CYAN, node->type, ANSI_RESET);

		// Print command
		printf("%s%s  %sCmd: %s", prefix, is_last ? "    " : "│   ", ANSI_GREEN, ANSI_RESET);
		if (node->cmd && node->cmd[0])
		{
			for (int i = 0; node->cmd[i]; i++)
				printf("%s ", node->cmd[i]);
			printf("\n");
		}
		else
		{
			printf("(none)\n");
		}

		// Print redirections
		printf("%s%s  %sRedirs: %s", prefix, is_last ? "    " : "│   ", ANSI_MAGENTA, ANSI_RESET);
		if (node->redirs)
		{
			printf("\n");
			t_redir *curr = node->redirs;
			while (curr)
			{
				printf("%s%s    %sIndex     : %s%zu\n", prefix, is_last ? "    " : "│   ",
					   ANSI_YELLOW, ANSI_RESET, curr->index);
				printf("%s%s    %sType      : %s%s\n", prefix, is_last ? "    " : "│   ",
					   ANSI_YELLOW, ANSI_RESET, get_redir_type_str(curr->type));
				printf("%s%s    %sFile      : %s%s\n", prefix, is_last ? "    " : "│   ",
					   ANSI_YELLOW, ANSI_RESET, curr->file ? curr->file : "(null)");
				printf("%s%s    %sFD        : %s%d\n", prefix, is_last ? "    " : "│   ",
					   ANSI_YELLOW, ANSI_RESET, curr->fd);
				curr = curr->next;
			}
		}
		else
		{
			printf("(none)\n");
		}
	}
	else if (node->type == NODE_PARENTHESES)
	{
		// Print parentheses node header
		printf("%s%s %sOperator Node: %s%s\n", prefix, is_last ? "└──" : "├──",
			   ANSI_CYAN, get_node_type_str(node->type), ANSI_RESET);

		// Print redirections
		printf("%s%s  %sRedirs: %s", prefix, is_last ? "    " : "│   ", ANSI_MAGENTA, ANSI_RESET);
		if (node->redirs)
		{
			printf("\n");
			t_redir *curr = node->redirs;
			while (curr)
			{
				printf("%s%s    %sIndex     : %s%zu\n", prefix, is_last ? "    " : "│   ",
					   ANSI_YELLOW, ANSI_RESET, curr->index);
				printf("%s%s    %sType      : %s%s\n", prefix, is_last ? "    " : "│   ",
					   ANSI_YELLOW, ANSI_RESET, get_redir_type_str(curr->type));
				printf("%s%s    %sFile      : %s%s\n", prefix, is_last ? "    " : "│   ",
					   ANSI_YELLOW, ANSI_RESET, curr->file ? curr->file : "(null)");
				printf("%s%s    %sFD        : %s%d\n", prefix, is_last ? "    " : "│   ",
					   ANSI_YELLOW, ANSI_RESET, curr->fd);
				curr = curr->next;
			}
		}
		else
		{
			printf("(none)\n");
		}
	}
	else
	{
		// Print other operator nodes
		printf("%s%s %sOperator Node: %s%s\n", prefix, is_last ? "└──" : "├──",
			   ANSI_YELLOW, get_node_type_str(node->type), ANSI_RESET);
	}
}

// Get annotation for a node
void get_node_annotation(t_tree *node, t_tree *parent, int is_left, char *buffer, size_t buf_size)
{
	char node_str[256];
	snprintf(node_str, sizeof(node_str), "%s", node->type == NODE_COMMAND ? "CMD" : get_node_type_str(node->type));

	if (!parent)
	{
		snprintf(buffer, buf_size, "%s// Root%s", ANSI_GREEN, ANSI_RESET);
	}
	else
	{
		char parent_str[256];
		snprintf(parent_str, sizeof(parent_str), "%s", parent->type == NODE_COMMAND ? "CMD" : get_node_type_str(parent->type));
		snprintf(buffer, buf_size, "%s// %s subtree of %s%s", ANSI_GREEN, is_left ? "Left" : "Right", parent_str, ANSI_RESET);
	}
}

// Recursive function to print tree
void print_tree_recursive(t_tree *node, char *prefix, int is_last, t_tree *parent, int is_left, int level)
{
	if (!node)
		return;

	// Print node details
	print_node_details(node, prefix, is_last);

	// Print annotation
	char annotation[512];
	get_node_annotation(node, parent, is_left, annotation, sizeof(annotation));
	printf("%s%s%s\n", prefix, is_last ? "    " : "│   ", annotation);

	// Prepare prefix for children
	char new_prefix[256];
	snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "    " : "│   ");

	// Recursively print children
	if (node->left || node->right)
	{
		if (node->left)
			print_tree_recursive(node->left, new_prefix, node->right == NULL, node, 1, level + 1);
		if (node->right)
			print_tree_recursive(node->right, new_prefix, 1, node, 0, level + 1);
	}
}
// Main function to print tree
void print_tree(t_tree *node)
{
	if (!node)
	{
		printf("%sEmpty tree%s\n", ANSI_RED, ANSI_RESET);
		return;
	}
	print_tree_recursive(node, "", 1, NULL, 0, 0);
}

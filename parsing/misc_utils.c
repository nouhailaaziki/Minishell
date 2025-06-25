/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:50:58 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/25 15:53:43 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

void init_shell(t_shell *shell)
{
	display_intro();
	shell->env_list = NULL;
	shell->line = NULL;
	shell->tokens = NULL;
	shell->current = NULL;
	shell->ast = NULL;

}

void print_redirs(t_redir *redir)
{
	while (redir)
	{
		printf(BLU"Redir type: ");
		if (redir->type == REDIR_IN)
			printf("REDIR_IN");
		else if (redir->type == REDIR_OUT)
			printf("REDIR_OUT");
		else if (redir->type == REDIR_APPEND)
			printf("REDIR_APPEND");
		else if (redir->type == REDIR_HEREDOC)
			printf("REDIR_HEREDOC");
		else
			printf("UNKNOWN");
		printf(", file: %s\n"RESET, redir->file);
		redir = redir->next;
	}
}

int ft_syntax_err(char *str)
{
	ft_putstr_fd("DeepShell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("'", 2);
	return 0;
}


void print_tokens(t_token **head)
{
	t_token *tmp;
	char * tiipe;

	tmp = *head;
	while (tmp)
	{
		if (tmp->type ==TOKEN_OR)
			tiipe = "OR";
		else if (tmp->type ==TOKEN_AND)
			tiipe = "AND";
		else if (tmp->type == REDIR_HEREDOC )
			tiipe = "REDIR_HEREDOC";
		else if (tmp->type == REDIR_APPEND )
			tiipe = "REDIR_APPEND";
		else if (tmp->type == REDIR_IN)
				tiipe = "REDIR_IN";
		else if (tmp->type == REDIR_OUT)
				tiipe = "REDIR_OUT";
		else if (tmp->type == TOKEN_PIPE )
			tiipe = "PIPE";
		else if (tmp->type == R_FILE)
			tiipe = "R_FILE";
		else if (tmp->type == TOKEN_ARG)
			tiipe = "ARGUMENT";
		else if (tmp->type == TOKEN_PAREN)
			tiipe = "PARENTHESE_BLOCK";
		else
			tiipe = "WORD";

		ft_printf(GRN"value : {%s}, type? : {%s}->{%d} , position : <%d>\n" RESET, (tmp)->value, tiipe , (tmp)->type, tmp->position);
		// if(tmp->prev != NULL && tmp->prev->value)
		// ft_printf("the one before the element %s, is %s", tmp->value , ÷tmp->prev->value);
		tmp = (tmp)->next;
	}
}
#include "launchpad.h"
#include <stdio.h>
#include <string.h>

/*-----------------------Format and Color Macros----------------------*/
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"
#define ORANGE "\x1b[38;5;214m"
#define PINK "\x1b[95m"
#define BOLD "\033[1m"

/*-----------------------Tree Drawing Characters----------------------*/
#define TREE_BRANCH "├──"
#define TREE_LAST "└──"
#define TREE_VERT "│  "
#define TREE_SPACE "   "

/*-----------------------Node Type String----------------------*/
static const char *get_node_type_string(t_node_type type)
{
	switch (type)
	{
	case NODE_COMMAND:
		return "COMMAND";
	case NODE_PIPE:
		return "PIPE";
	case NODE_AND:
		return "AND";
	case NODE_OR:
		return "OR";
	case NODE_PARENTHESES:
		return "PARENTHS";
	default:
		return "UNKNOWN";
	}
}

/*-----------------------Node Type Color----------------------*/
static const char *get_node_color(t_node_type type)
{
	switch (type)
	{
	case NODE_COMMAND:
		return COLOR_GREEN;
	case NODE_PIPE:
		return COLOR_BLUE;
	case NODE_AND:
		return COLOR_YELLOW;
	case NODE_OR:
		return ORANGE;
	case NODE_PARENTHESES:
		return PINK;
	default:
		return COLOR_WHITE;
	}
}

/*-----------------------Redir Type String----------------------*/
static const char *get_redir_type_string(t_token_type type)
{
	switch (type)
	{
	case REDIR_IN:
		return "<";
	case REDIR_OUT:
		return ">";
	case REDIR_APPEND:
		return ">>";
	case REDIR_HEREDOC:
		return "<<";
	default:
		return "?";
	}
}

/*-----------------------Token Type String----------------------*/
static const char *get_token_type_string(t_token_type type)
{
	switch (type)
	{
	case TOKEN_WORD:
		return "WORD";
	case TOKEN_ARG:
		return "ARG";
	case TOKEN_PAREN:
		return "PAREN";
	case TOKEN_PAREN_LEFT:
		return "PAREN_LEFT";
	case TOKEN_PAREN_RIGHT:
		return "PAREN_RIGHT";
	case TOKEN_AND:
		return "AND";
	case TOKEN_OR:
		return "OR";
	case TOKEN_PIPE:
		return "PIPE";
	case TOKEN_REDIR:
		return "REDIR";
	case R_FILE:
		return "R_FILE";
	case REDIR_IN:
		return "REDIR_IN";
	case REDIR_OUT:
		return "REDIR_OUT";
	case REDIR_APPEND:
		return "REDIR_APPEND";
	case REDIR_HEREDOC:
		return "REDIR_HEREDOC";
	default:
		return "UNKNOWN";
	}
}

/*-----------------------Token Type Color----------------------*/
static const char *get_token_color(t_token_type type)
{
	switch (type)
	{
	case TOKEN_WORD:
	case TOKEN_ARG:
		return COLOR_WHITE;
	case TOKEN_AND:
	case TOKEN_OR:
		return COLOR_YELLOW;
	case TOKEN_PIPE:
		return COLOR_BLUE;
	case TOKEN_REDIR:
	case REDIR_IN:
	case REDIR_OUT:
	case REDIR_APPEND:
	case REDIR_HEREDOC:
		return COLOR_CYAN;
	case R_FILE:
		return COLOR_MAGENTA;
	case TOKEN_PAREN:
		return COLOR_GREEN;
	case TOKEN_PAREN_LEFT:
	case TOKEN_PAREN_RIGHT:
		return PINK;
	default:
		return COLOR_WHITE;
	}
}

/*-----------------------Tree Utilities----------------------*/
static int calculate_tree_depth(t_tree *node)
{
	if (!node)
		return 0;
	int ld = calculate_tree_depth(node->left);
	int rd = calculate_tree_depth(node->right);
	return 1 + (ld > rd ? ld : rd);
}

static int count_tree_nodes(t_tree *node)
{
	if (!node)
		return 0;
	return 1 + count_tree_nodes(node->left) + count_tree_nodes(node->right);
}

/*-----------------------Redirection Print----------------------*/
static void print_redirections(t_redir *r, const char *prefix)
{
	int i = 0;
	for (; r; r = r->next, ++i)
	{
		const char *mark = r->next ? TREE_BRANCH : TREE_LAST;
		printf("%s%s %s[%zu] %s%s%s → \"%s\"%s",
			   prefix,
			   mark,
			   COLOR_CYAN,
			   r->index,
			   COLOR_CYAN,
			   get_redir_type_string(r->type),
			   COLOR_WHITE,
			   r->file ? r->file : "NULL",
			   COLOR_RESET);
		if (r->fd != -1 || r->flag)
			printf(" %s(fd:%d,flag:%d)%s", COLOR_WHITE, r->fd, r->flag, COLOR_RESET);
		printf("\n");
	}
}
/*-----------------------Command Args Print----------------------*/
static void print_command_args(char **cmd, const char *prefix, int is_last)
{
	const char *mark = is_last ? TREE_LAST : TREE_BRANCH;
	if (!cmd || !cmd[0])
	{
		printf("%s%s %sCommand: %s(empty)%s\n",
			   prefix, mark, COLOR_GREEN, COLOR_RED, COLOR_RESET);
		return;
	}
	printf("%s%s %sCommand: %s\"%s\"%s",
		   prefix, mark, COLOR_GREEN, COLOR_YELLOW, cmd[0], COLOR_RESET);
	for (int i = 1; cmd[i]; ++i)
		printf(" \"%s\"", cmd[i]);
	printf("\n");
}

/*-----------------------Recursive Tree Printer----------------------*/
static void visualize_tree_recursive(t_tree *node,
									 const char *prefix,
									 int is_last)
{
	if (!node)
	{
		printf("%s%s%s(null)%s\n", prefix, TREE_LAST, COLOR_RED, COLOR_RESET);
		return;
	}

	// Print the current node's line
	const char *branch = is_last ? TREE_LAST : TREE_BRANCH;
	const char *ncol = get_node_color(node->type);
	printf("%s%s %s%s%s %s[%s%s%s]%s (argc: %zu)%s\n",
		   prefix,
		   branch,
		   ncol,
		   get_node_type_string(node->type),
		   COLOR_RESET,
		   COLOR_WHITE,
		   node->is_ambiguous ? COLOR_RED : COLOR_GREEN,
		   node->is_ambiguous ? "AMBIGUOUS" : "OK",
		   COLOR_WHITE,
		   COLOR_RESET,
		   node->argc,
		   COLOR_RESET);

	// Prepare the prefix for all children and details of this node
	char next_prefix[1024];
	snprintf(next_prefix, sizeof(next_prefix), "%s%s", prefix, is_last ? TREE_SPACE : TREE_VERT);

	// Print command details + redirs using the new, correct prefix
	if (node->type == NODE_COMMAND)
	{
		// Pass the next_prefix, and tell it if it's the last detail line
		print_command_args(node->cmd, next_prefix, node->redirs == NULL);
		if (node->redirs)
			print_redirections(node->redirs, next_prefix);
	}

	// Recurse for left/right children
	if (node->left || node->right)
	{
		if (node->left)
		{
			// Use next_prefix to indent the "Left:" label correctly
			printf("%s%sLeft:%s\n", next_prefix, COLOR_YELLOW, COLOR_RESET);
			visualize_tree_recursive(node->left, next_prefix, node->right == NULL);
		}
		if (node->right)
		{
			// Use next_prefix to indent the "Right:" label correctly
			printf("%s%sRight:%s\n", next_prefix, COLOR_YELLOW, COLOR_RESET);
			visualize_tree_recursive(node->right, next_prefix, 1);
		}
	}
}
/*-----------------------AST Visualizer Entry Point----------------------*/
void visualize_ast_tree(t_tree *root)
{
	if (!root)
	{
		printf("%sAST Tree: (empty)%s\n", COLOR_RED, COLOR_RESET);
		return;
	}
	int depth = calculate_tree_depth(root);
	int nodes = count_tree_nodes(root);

	// Header box
	printf("\n%s╔══════════════════════════════════╗%s\n", COLOR_CYAN, COLOR_RESET);
	printf("%s║   %sAST TREE VISUALIZER%s   ║%s\n",
		   COLOR_CYAN, COLOR_WHITE, COLOR_CYAN, COLOR_RESET);
	printf("%s║ Depth: %-2d │ Nodes: %-2d ║%s\n",
		   COLOR_CYAN, depth, nodes, COLOR_RESET);
	printf("%s╚══════════════════════════════════╝%s\n\n", COLOR_CYAN, COLOR_RESET);

	visualize_tree_recursive(root, "", 1);

	// --- LEGEND (FIXED) ---
	printf("\n%sLegend:%s\n", BOLD, COLOR_RESET);
	printf("  %sNode Types: %sCOMMAND%s, %sPIPE%s, %sAND%s, %sOR%s, %sPARENTHS%s\n",
		   COLOR_WHITE,
		   get_node_color(NODE_COMMAND), COLOR_RESET,
		   get_node_color(NODE_PIPE), COLOR_RESET,
		   get_node_color(NODE_AND), COLOR_RESET,
		   get_node_color(NODE_OR), COLOR_RESET,
		   get_node_color(NODE_PARENTHESES), COLOR_RESET);

	printf("  %sTokens:     %sWORD/ARG%s, %sOPERATOR%s, %sREDIR%s, %sFILENAME%s, %sPARENTHESES%s\n",
		   COLOR_WHITE,
		   get_token_color(TOKEN_WORD), COLOR_RESET,
		   get_token_color(TOKEN_AND), COLOR_RESET,
		   get_token_color(TOKEN_REDIR), COLOR_RESET,
		   get_token_color(R_FILE), COLOR_RESET,
		   get_token_color(TOKEN_PAREN_LEFT), COLOR_RESET);

	printf("  %sStatus:     %sOK%s, %sAMBIGUOUS%s\n",
		   COLOR_WHITE,
		   COLOR_GREEN, COLOR_RESET,
		   COLOR_RED, COLOR_RESET);
	printf("\n");
}
/*-----------------------Token List Visualizer----------------------*/
/*-----------------------Token List Visualizer----------------------*/
// FIX: Updated to use the token's color for the tree branch and index.
// Also improved the header box for better centering.
void visualize_tokens(t_token *head)
{
	if (!head)
	{
		printf("%sToken List: (empty)%s\n", COLOR_RED, COLOR_RESET);
		return;
	}
	printf("\n%s╔══════════════════════════════════╗%s\n", COLOR_CYAN, COLOR_RESET);
	printf("%s║        %sTOKEN VISUALIZER%s          ║%s\n",
		   COLOR_CYAN, BOLD, COLOR_CYAN, COLOR_RESET);
	printf("%s╚══════════════════════════════════╝%s\n", COLOR_CYAN, COLOR_RESET);

	// Add a small indent for the list
	if (!head->next)
		printf("  ");

	int idx = 0;
	for (t_token *cur = head; cur; cur = cur->next, ++idx)
	{
		const char *mark = cur->next ? TREE_BRANCH : TREE_LAST;
		const char *tcol = get_token_color(cur->type);
		printf("  %s%s [%02d]%s %s%-14s%s \"%s\" %s(pos:%d)%s\n",
			   tcol,
			   mark,
			   idx,
			   COLOR_RESET,
			   tcol,
			   get_token_type_string(cur->type),
			   COLOR_RESET,
			   cur->value ? cur->value : "NULL",
			   COLOR_WHITE,
			   cur->position,
			   COLOR_RESET);
	}
	printf("\n");
}

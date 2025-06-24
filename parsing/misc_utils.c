/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:50:58 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/24 16:28:52 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

void init_shell(t_shell *shell)
{
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
#include <stdlib.h>
#include <string.h>

// ANSI color codes for different node types
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"

// Tree drawing characters
#define TREE_BRANCH "├──"
#define TREE_LAST   "└──"
#define TREE_VERT   "│  "
#define TREE_SPACE  "   "

/**
 * Get the string representation of a node type
 */
static const char *get_node_type_string(t_node_type type)
{
    switch (type)
    {
    case NODE_COMMAND:  return "COMMAND";
    case NODE_PIPE:     return "PIPE";
    case NODE_AND:      return "AND";
    case NODE_OR:       return "OR";
    case NODE_PARENTHS: return "PARENTHS";
    default:            return "UNKNOWN";
    }
}

/**
 * Get the color for a node type
 */
static const char *get_node_color(t_node_type type)
{
    switch (type)
    {
    case NODE_COMMAND:  return COLOR_GREEN;
    case NODE_PIPE:     return COLOR_BLUE;
    case NODE_AND:      return COLOR_YELLOW;
    case NODE_OR:       return COLOR_RED;
    case NODE_PARENTHS: return COLOR_MAGENTA;
    default:            return COLOR_WHITE;
    }
}

/**
 * Get the string representation of a redirection type
 */
static const char *get_redir_type_string(t_token_type type)
{
    switch (type)
    {
    case REDIR_IN:      return "<";
    case REDIR_OUT:     return ">";
    case REDIR_APPEND:  return ">>";
    case REDIR_HEREDOC: return "<<";
    default:            return "?";
    }
}

/**
 * Get the string representation of a token type
 */
static const char *get_token_type_string(t_token_type type)
{
    switch (type)
    {
    case TOKEN_WORD:        return "WORD";
    case TOKEN_ARG:         return "ARG";
    case TOKEN_AND:         return "AND";
    case TOKEN_OR:          return "OR";
    case REDIR_IN:          return "REDIR_IN";
    case REDIR_OUT:         return "REDIR_OUT";
    case TOKEN_PIPE:        return "PIPE";
    case REDIR_APPEND:      return "REDIR_APPEND";
    case REDIR_HEREDOC:     return "REDIR_HEREDOC";
    case R_FILE:            return "R_FILE";
    case TOKEN_PAREN_LEFT:  return "PAREN_LEFT";
    case TOKEN_PAREN_RIGHT: return "PAREN_RIGHT";
    default:                return "UNKNOWN";
    }
}

/**
 * Get the display color for a token type
 */
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
	case REDIR_IN:
	case REDIR_OUT:
	case REDIR_APPEND:
	case REDIR_HEREDOC:
		return COLOR_CYAN;
	case TOKEN_PIPE:
		return COLOR_BLUE;
	case R_FILE:
		return COLOR_MAGENTA;
	case TOKEN_PAREN_LEFT:
	case TOKEN_PAREN_RIGHT:
		return COLOR_MAGENTA;
	default:
		return COLOR_WHITE;
	}
}

/**
 * Calculate the depth of the AST
 */
static int calculate_tree_depth(t_tree *node)
{
    if (!node) return 0;
    int ld = calculate_tree_depth(node->left);
    int rd = calculate_tree_depth(node->right);
    return 1 + (ld > rd ? ld : rd);
}

/**
 * Count total nodes in the AST
 */
static int count_tree_nodes(t_tree *node)
{
    if (!node) return 0;
    return 1 + count_tree_nodes(node->left) + count_tree_nodes(node->right);
}

/**
 * Print a linked list of redirections
 */
static void print_redirections(t_redir *r, const char *prefix)
{
	int i = 0;
	for (; r; r = r->next, ++i)
	{
		const char *mark = r->next ? "├─" : "└─";
		printf("%s    %s│ %s[%d] %s%s%s → \"%s\"%s",
			   prefix,
			   COLOR_CYAN,
			   mark,
			   i,
			   COLOR_CYAN,
			   get_redir_type_string(r->type),
			   COLOR_WHITE,
			   r->file ? r->file : "NULL",
			   COLOR_RESET);
		if (r->fd != -1 || r->flag)
			printf(" %s(fd:%d,flag:%d)%s", COLOR_WHITE, r->fd, r->flag, COLOR_RESET);
		printf("\n");
	}

	if (count > 0)
		printf("%s%s└─ %sTotal: %d redirection%s%s\n",
			   prefix,
			   COLOR_CYAN,
			   COLOR_WHITE,
			   count,
			   count == 1 ? "" : "s",
			   COLOR_RESET);
}

/**
 * Print command node details (args, etc.)
 */
static void print_command_args(char **cmd, const char *prefix)
{
	if (!cmd || !cmd[0])
	{
		printf("%s    %s┌─ Command: %s(empty)%s\n",
			   prefix, COLOR_GREEN, COLOR_RED, COLOR_RESET);
		return;
	}
	printf("%s    %s┌─ Command: %s\"%s\"%s",
		   prefix, COLOR_GREEN, COLOR_YELLOW, cmd[0], COLOR_RESET);
	if (cmd[1])
	{
		printf(" %sArgs:%s", COLOR_GREEN, COLOR_RESET);
		for (int i = 1; cmd[i]; ++i)
			printf(" \"%s\"", cmd[i]);
	}
	printf("\n");

	if (i > 1)
	{
		printf("%s%s└─ Arguments: %d%s\n",
			   prefix, COLOR_GREEN, i - 1, COLOR_RESET);
	}
}

/**
 * Recursive AST printer
 */
static void visualize_tree_recursive(t_tree *node,
                                     const char *prefix,
                                     int is_last)
{
	char np[1024];
	if (!node)
	{
		printf("%s%s(null)%s\n", prefix, COLOR_RED, COLOR_RESET);
		return;
	}
	const char *branch = is_last ? TREE_LAST : TREE_BRANCH;
	const char *ncol = get_node_color(node->type);
	printf("%s%s %s%s%s %s[%s%s%s]%s\n",
		   prefix,
		   branch,
		   ncol,
		   get_node_type_string(node->type),
		   COLOR_WHITE,
		   node->is_ambiguous ? COLOR_RED : COLOR_GREEN,
		   node->is_ambiguous ? "AMBIGUOUS" : "OK",
		   COLOR_WHITE,
		   COLOR_RESET);

	// Print command details + redirs
	if (node->type == NODE_COMMAND)
	{
		print_command_args(node->cmd, new_prefix);

		// Print redirections with enhanced formatting
		if (node->redirs)
			print_redirections(node->redirs, new_prefix);

	// Prepare prefix for children
	snprintf(np, sizeof(np), "%s%s", prefix, is_last ? TREE_SPACE : TREE_VERT);

	// Recurse left/right
	if (node->left)
	{
		printf("%s%s Left:%s\n", prefix, COLOR_YELLOW, COLOR_RESET);
		visualize_tree_recursive(node->left, np, node->right == NULL);
	}
	if (node->right)
	{
		printf("%s%s Right:%s\n", prefix, COLOR_YELLOW, COLOR_RESET);
		visualize_tree_recursive(node->right, np, 1);
	}
}

/**
 * Entry point for AST visualization
 */
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

	// Legend
	printf("\n%sLegend:%s\n", COLOR_WHITE, COLOR_RESET);
	printf("  %sNode Types:%s COMMAND=● GREEN, PIPE=● BLUE, AND=● YELLOW, OR=● RED, PARENTHS=● MAGENTA\n",
		   COLOR_WHITE, COLOR_RESET);
	printf("  %sTokens:%s WORD/ARG=WHITE, AND/OR=YELLOW, REDIR=CYAN, PIPE=BLUE, R_FILE=MAGENTA,\n"
		   "           %sPAREN_LEFT/RIGHT=● MAGENTA\n",
		   COLOR_WHITE, COLOR_RESET, COLOR_MAGENTA);
	printf("  %sPosition: integer index in token list%s\n\n",
		   COLOR_WHITE, COLOR_RESET);
}

/**
 * Token list visualizer, now with integer position and paren tokens
 */
void visualize_tokens(t_token *head)
{
	if (!head)
	{
		printf("%sToken List: (empty)%s\n", COLOR_RED, COLOR_RESET);
		return;
	}
	printf("\n%s╔══════════════════════════════════╗%s\n", COLOR_CYAN, COLOR_RESET);
	printf("%s║     %sTOKEN VISUALIZER%s     ║%s\n",
		   COLOR_CYAN, COLOR_WHITE, COLOR_CYAN, COLOR_RESET);
	printf("%s╚══════════════════════════════════╝%s\n\n", COLOR_CYAN, COLOR_RESET);

	int idx = 0;
	for (t_token *cur = head; cur; cur = cur->next, ++idx)
	{
		const char *mark = cur->next ? TREE_BRANCH : TREE_LAST;
		const char *tcol = get_token_color(cur->type);
		printf("%s%s [%02d] %s%-12s%s \"%s\" %s(pos:%d)%s\n",
			   COLOR_CYAN,
			   mark,
			   idx,
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

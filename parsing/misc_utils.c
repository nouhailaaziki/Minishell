/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:50:58 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/19 18:16:39 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

void refresh_block(t_token **head)
{
	while (*head && (*head)->prev && (*head)->prev->type != TOKEN_PIPE \
	 && (*head)->prev->type != TOKEN_AND && (*head)->prev->type != TOKEN_OR)
		*head = (*head)->prev;
}
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

int ft_syntax_err(char *str, t_token **head)
{
	(void)head;
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
// ANSI color codes for different node types
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"

// Tree drawing characters - FIXED: Simple and consistent
#define TREE_BRANCH "├──"
#define TREE_LAST "└──"
#define TREE_VERT "│  "
#define TREE_SPACE "   "

/**
 * Get the string representation of a node type
 */
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
	case NODE_PARENTHS:
		return "PARENTHS";
	default:
		return "UNKNOWN";
	}
}

/**
 * Get the color for a node type
 */
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
		return COLOR_RED;
	case NODE_PARENTHS:
		return COLOR_MAGENTA;
	default:
		return COLOR_WHITE;
	}
}

/**
 * Get the string representation of a redirection type
 */
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

/**
 * Get the string representation of a token type
 */
static const char *get_token_type_string(t_token_type type)
{
	switch (type)
	{
	case TOKEN_WORD:
		return "WORD";
	case TOKEN_ARG:
		return "ARG";
	case TOKEN_AND:
		return "AND";
	case TOKEN_OR:
		return "OR";
	case REDIR_IN:
		return "REDIR_IN";
	case REDIR_OUT:
		return "REDIR_OUT";
	case TOKEN_PIPE:
		return "PIPE";
	case REDIR_APPEND:
		return "REDIR_APPEND";
	case REDIR_HEREDOC:
		return "REDIR_HEREDOC";
	case R_FILE:
		return "R_FILE";
	case TOKEN_PAREN:
		return "TOKEN_PAREN";
	default:
		return "UNKNOWN";
	}
}

/**
 * Get color for token type
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
	case TOKEN_PAREN:
		return COLOR_GREEN;
	default:
		return COLOR_WHITE;
	}
}

/**
 * Calculate the depth of the tree
 */
static int calculate_tree_depth(t_tree *node)
{
	int left_depth, right_depth;

	if (!node)
		return 0;

	left_depth = calculate_tree_depth(node->left);
	right_depth = calculate_tree_depth(node->right);

	return 1 + (left_depth > right_depth ? left_depth : right_depth);
}

/**
 * Count the total number of nodes in the tree
 */
static int count_tree_nodes(t_tree *node)
{
	if (!node)
		return 0;

	return 1 + count_tree_nodes(node->left) + count_tree_nodes(node->right);
}

/**
 * Print redirection information
 */
static void print_redirections(t_redir *redirs, const char *prefix)
{
	t_redir *current;
	int count;

	if (!redirs)
		return;

	printf("%s    %s┌─ Redirections:%s\n", prefix, COLOR_CYAN, COLOR_RESET);

	current = redirs;
	count = 0;
	while (current)
	{
		const char *marker = (current->next) ? "├─" : "└─";

		printf("%s    %s│ %s [%d] %s%s%s → \"%s\"%s",
			   prefix,
			   COLOR_CYAN,
			   marker,
			   count++,
			   COLOR_CYAN,
			   get_redir_type_string(current->type),
			   COLOR_WHITE,
			   current->file ? current->file : "NULL",
			   COLOR_RESET);

		if (current->fd != -1 || current->flag != 0)
			printf(" %s(fd:%d, flag:%d)%s", COLOR_WHITE, current->fd, current->flag, COLOR_RESET);

		printf("\n");
		current = current->next;
	}
}

/**
 * Print command arguments
 */
static void print_command_args(char **cmd, const char *prefix)
{
	int i;

	if (!cmd || !cmd[0])
	{
		printf("%s    %s┌─ Command: %s(empty)%s\n", prefix, COLOR_GREEN, COLOR_RED, COLOR_RESET);
		return;
	}

	printf("%s    %s┌─ Command: %s\"%s\"%s",
		   prefix, COLOR_GREEN, COLOR_YELLOW, cmd[0], COLOR_RESET);

	if (cmd[1])
	{
		printf(" %sArgs:%s", COLOR_GREEN, COLOR_RESET);
		for (i = 1; cmd[i]; i++)
			printf(" \"%s\"", cmd[i]);
	}
	printf("\n");
}

/**
 * FIXED: Properly aligned recursive function
 */
static void visualize_tree_recursive(t_tree *node, const char *prefix, int is_last)
{
	char new_prefix[1024];
	const char *branch;
	const char *node_color;
	int has_redirections;

	if (!node)
	{
		printf("%s%s%s(null)%s\n", prefix, TREE_LAST, COLOR_RED, COLOR_RESET);
		return;
	}

	// Choose branch character
	branch = is_last ? TREE_LAST : TREE_BRANCH;
	node_color = get_node_color(node->type);
	has_redirections = (node->redirs != NULL);

	// Print current node
	printf("%s%s %s%s%s %s[%s%s%s]%s",
		   prefix,
		   branch,
		   node_color,
		   get_node_type_string(node->type),
		   COLOR_RESET,
		   COLOR_WHITE,
		   node->is_ambiguous ? COLOR_RED : COLOR_GREEN,
		   node->is_ambiguous ? "AMBIGUOUS" : "OK",
		   COLOR_WHITE,
		   COLOR_RESET);

	if (node->type == NODE_COMMAND)
	{
		printf(" %s(argc: %zu", COLOR_WHITE, node->argc);
		if (has_redirections)
			printf(", redirs: ✓");
		printf(")%s", COLOR_RESET);
	}
	printf("\n");

	// Print command details for command nodes
	if (node->type == NODE_COMMAND)
	{
		print_command_args(node->cmd, prefix);
		if (node->redirs)
			print_redirections(node->redirs, prefix);
	}

	// Create new prefix for children - FIXED: Proper prefix calculation
	snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? TREE_SPACE : TREE_VERT);

	// Print children
	if (node->left || node->right)
	{
		if (node->left)
		{
			printf("%s %s├─ Left:%s\n", prefix, COLOR_YELLOW, COLOR_RESET);
			visualize_tree_recursive(node->left, new_prefix, !node->right);
		}

		if (node->right)
		{
			printf("%s %s└─ Right:%s\n", prefix, COLOR_YELLOW, COLOR_RESET);
			visualize_tree_recursive(node->right, new_prefix, 1);
		}
	}
}

/**
 * Main function to visualize the AST tree
 */
void visualize_ast_tree(t_tree *root)
{
	int depth, node_count;

	if (!root)
	{
		printf("%sAST Tree: (empty)%s\n", COLOR_RED, COLOR_RESET);
		return;
	}

	depth = calculate_tree_depth(root);
	node_count = count_tree_nodes(root);

	// Print header
	printf("\n%s╔═══════════════════════════════════════════╗%s\n", COLOR_CYAN, COLOR_RESET);
	printf("%s║             %sAST TREE VISUALIZER%s             ║%s\n",
		   COLOR_CYAN, COLOR_WHITE, COLOR_CYAN, COLOR_RESET);
	printf("%s║   Depth: %-3d    │    Nodes: %-3d      ║%s\n",
		   COLOR_CYAN, depth, node_count, COLOR_RESET);
	printf("%s╚═══════════════════════════════════════════╝%s\n\n", COLOR_CYAN, COLOR_RESET);

	// Visualize the tree with empty prefix
	visualize_tree_recursive(root, "", 1);

	// Print legend
	printf("\n%s═══════════════════════════════════════════%s\n", COLOR_CYAN, COLOR_RESET);
	printf("%sLegend:%s\n", COLOR_WHITE, COLOR_RESET);
	printf("  %sNode Types:%s\n", COLOR_WHITE, COLOR_RESET);
	printf("    %s●%s COMMAND   %s●%s PIPE   %s●%s AND   %s●%s OR   %s●%s PARENTHS\n",
		   COLOR_GREEN, COLOR_RESET, COLOR_BLUE, COLOR_RESET,
		   COLOR_YELLOW, COLOR_RESET, COLOR_RED, COLOR_RESET,
		   COLOR_MAGENTA, COLOR_RESET);
	printf("  %sRedirections:%s\n", COLOR_WHITE, COLOR_RESET);
	printf("    %s<%s Input   %s>%s Output   %s>>%s Append   %s<<%s Heredoc\n",
		   COLOR_CYAN, COLOR_RESET, COLOR_CYAN, COLOR_RESET,
		   COLOR_CYAN, COLOR_RESET, COLOR_CYAN, COLOR_RESET);
	printf("%s═══════════════════════════════════════════%s\n\n", COLOR_CYAN, COLOR_RESET);
}

/**
 * Print a simplified flat representation of the tree
 */
void print_flat_ast(t_tree *node, int level)
{
	int i;

	if (!node)
		return;

	// Prevent infinite recursion
	if (level > 50)
	{
		printf("%*s%s[Max depth reached]%s\n", level * 2, "", COLOR_RED, COLOR_RESET);
		return;
	}

	// Print indentation with consistent spacing
	for (i = 0; i < level; i++)
		printf("  ");

	printf("%s%s%s",
		   get_node_color(node->type),
		   get_node_type_string(node->type),
		   COLOR_RESET);

	if (node->type == NODE_COMMAND && node->cmd && node->cmd[0])
		printf(": %s", node->cmd[0]);

	printf("\n");

	// Recursively print children
	print_flat_ast(node->left, level + 1);
	print_flat_ast(node->right, level + 1);
}

/**
 * Visualize token list
 */
void visualize_tokens(t_token *head)
{
	t_token *current;
	int count;

	if (!head)
	{
		printf("%sToken List: (empty)%s\n", COLOR_RED, COLOR_RESET);
		return;
	}

	// Print header
	printf("\n%s╔═══════════════════════════════════════════╗%s\n", COLOR_CYAN, COLOR_RESET);
	printf("%s║             %sTOKEN VISUALIZER%s              ║%s\n",
		   COLOR_CYAN, COLOR_WHITE, COLOR_CYAN, COLOR_RESET);
	printf("%s╚═══════════════════════════════════════════╝%s\n\n", COLOR_CYAN, COLOR_RESET);

	current = head;
	count = 0;

	while (current)
	{
		const char *token_color = get_token_color(current->type);
		const char *marker = (current->next) ? TREE_BRANCH : TREE_LAST;

		printf("%s%s [%02d] %s%-12s%s \"%s%s%s\"",
			   COLOR_CYAN,
			   marker,
			   count++,
			   token_color,
			   get_token_type_string(current->type),
			   COLOR_RESET,
			   COLOR_WHITE,
			   current->value ? current->value : "NULL",
			   COLOR_RESET);

		if (current->position > 0)
			printf(" %s(pos: %d)%s", COLOR_WHITE, current->position, COLOR_RESET);

		printf("\n");
		current = current->next;
	}

	printf("\n%s═══════════════════════════════════════════%s\n", COLOR_CYAN, COLOR_RESET);
	printf("%sToken Legend:%s\n", COLOR_WHITE, COLOR_RESET);
	printf("  %s●%s WORD/ARG   %s●%s OPERATORS   %s●%s REDIRECTIONS   %s●%s PIPE   %s●%s R_FILE   %s●%s PAREN\n",
		   COLOR_WHITE, COLOR_RESET, COLOR_YELLOW, COLOR_RESET,
		   COLOR_CYAN, COLOR_RESET, COLOR_BLUE, COLOR_RESET,
		   COLOR_MAGENTA, COLOR_RESET, COLOR_GREEN, COLOR_RESET);
	printf("%s═══════════════════════════════════════════%s\n\n", COLOR_CYAN, COLOR_RESET);
}

/**
 * Export token list to a readable format
 */
void export_tokens_to_file(t_token *head, const char *filename)
{
	FILE *file;
	t_token *current;
	int count;

	if (!filename)
	{
		printf("Error: Invalid filename\n");
		return;
	}

	file = fopen(filename, "w");
	if (!file)
	{
		printf("Error: Could not create file %s\n", filename);
		return;
	}

	fprintf(file, "Token List Export\n");
	fprintf(file, "=================\n\n");

	if (!head)
	{
		fprintf(file, "Token list is empty.\n");
		fclose(file);
		return;
	}

	current = head;
	count = 0;

	fprintf(file, "Index | Type         | Value            | Position\n");
	fprintf(file, "------|--------------|------------------|----------\n");

	while (current)
	{
		fprintf(file, "%-5d | %-12s | %-16s | %d\n",
				count++,
				get_token_type_string(current->type),
				current->value ? current->value : "NULL",
				current->position);
		current = current->next;
	}

	fprintf(file, "\nTotal tokens: %d\n", count);
	fclose(file);

	printf("Tokens exported to %s\n", filename);
}

/**
 * Display both tokens and AST tree
 */
void visualize_parsing_process(t_token *tokens, t_tree *ast)
{
	printf("\n%s╔═══════════════════════════════════════════════════════════════╗%s\n", COLOR_CYAN, COLOR_RESET);
	printf("%s║                    %sPARSING PROCESS VISUALIZER%s                    ║%s\n",
		   COLOR_CYAN, COLOR_WHITE, COLOR_CYAN, COLOR_RESET);
	printf("%s╚═══════════════════════════════════════════════════════════════╝%s\n", COLOR_CYAN, COLOR_RESET);

	printf("\n%s1. TOKENIZATION RESULT:%s\n", COLOR_YELLOW, COLOR_RESET);
	visualize_tokens(tokens);

	printf("\n%s2. AST CONSTRUCTION RESULT:%s\n", COLOR_YELLOW, COLOR_RESET);
	visualize_ast_tree(ast);

	printf("%s═══════════════════════════════════════════════════════════════%s\n", COLOR_CYAN, COLOR_RESET);
}

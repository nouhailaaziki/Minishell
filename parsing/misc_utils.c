/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:50:58 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/18 10:35:41 by yrhandou         ###   ########.fr       */
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

int ft_syntax_err(char *str, t_token **head)
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

// ANSI color codes for different node types
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"

// Tree drawing characters
#define TREE_VERTICAL "│"
#define TREE_BRANCH "├──"
#define TREE_LAST "└──"
#define TREE_SPACE "    "
#define TREE_CONTINUE "│   "

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

	printf("%s%s┌─ Redirections:%s\n", prefix, COLOR_CYAN, COLOR_RESET);

	current = redirs;
	count = 0;
	while (current)
	{
		const char *next_marker = (current->next) ? "├─" : "└─";

		printf("%s%s│ %s[%d] %s%s%s %s→%s %s\"%s\"%s",
			   prefix,
			   COLOR_CYAN,
			   next_marker,
			   count++,
			   COLOR_CYAN,
			   get_redir_type_string(current->type),
			   COLOR_RESET,
			   COLOR_WHITE,
			   COLOR_RESET,
			   COLOR_WHITE,
			   current->file ? current->file : "NULL",
			   COLOR_RESET);

		// Add fd and flag info if they're meaningful
		if (current->fd != -1 || current->flag != 0)
		{
			printf(" %s(fd:%d, flag:%d)%s",
				   COLOR_WHITE,
				   current->fd,
				   current->flag,
				   COLOR_RESET);
		}

		printf("\n");
		current = current->next;
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
 * Enhanced command arguments display with better formatting
 */
static void print_command_args(char **cmd, const char *prefix)
{
	int i;

	if (!cmd)
	{
		printf("%s%s┌─ Args: %sNULL%s\n", prefix, COLOR_GREEN, COLOR_RED, COLOR_RESET);
		return;
	}

	printf("%s%s┌─ Command:%s ", prefix, COLOR_GREEN, COLOR_RESET);
	i = 0;
	while (cmd[i])
	{
		if (i == 0)
			printf("%s\"%s\"%s", COLOR_YELLOW, cmd[i], COLOR_RESET); // Highlight command name
		else
			printf("%s\"%s\"%s", COLOR_WHITE, cmd[i], COLOR_RESET);

		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");

	if (i > 1)
	{
		printf("%s%s└─ Arguments: %d%s\n",
			   prefix, COLOR_GREEN, i - 1, COLOR_RESET);
	}
}

/**
 * Recursive function to visualize the tree
 */
static void visualize_tree_recursive(t_tree *node, const char *prefix, int is_last, int depth)
{
	char new_prefix[1024];
	const char *branch_char;
	const char *node_color;
	int has_redirections;

	if (!node)
	{
		printf("%s%s(null)%s\n", prefix, COLOR_RED, COLOR_RESET);
		return;
	}

	// Choose the appropriate branch character
	branch_char = is_last ? TREE_LAST : TREE_BRANCH;
	node_color = get_node_color(node->type);

	// Check if node has any redirections
	has_redirections = (node->redirs != NULL);

	// Print current node with additional info
	printf("%s%s%s%s %s[%s%s%s]%s",
		   prefix,
		   branch_char,
		   node_color,
		   get_node_type_string(node->type),
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

	// Create new prefix for children
	snprintf(new_prefix, sizeof(new_prefix), "%s%s",
			 prefix, is_last ? TREE_SPACE : TREE_CONTINUE);

	// Print command details if it's a command node
	if (node->type == NODE_COMMAND)
	{
		print_command_args(node->cmd, new_prefix);

		// Print redirections with enhanced formatting
		if (node->redirs)
			print_redirections(node->redirs, new_prefix);

		// Add a separator line if there were redirections and there are children
		if (has_redirections && (node->left || node->right))
			printf("%s%s│%s\n", new_prefix, COLOR_CYAN, COLOR_RESET);
	}

	// Recursively print children
	if (node->left || node->right)
	{
		if (node->left)
		{
			printf("%s%s├─ Left:%s\n", new_prefix, COLOR_YELLOW, COLOR_RESET);
			snprintf(new_prefix, sizeof(new_prefix), "%s%s",
					 prefix, is_last ? TREE_SPACE : TREE_CONTINUE);
			strcat(new_prefix, "│   ");
			visualize_tree_recursive(node->left, new_prefix, !node->right, depth + 1);
		}

		if (node->right)
		{
			printf("%s%s└─ Right:%s\n", new_prefix, COLOR_YELLOW, COLOR_RESET);
			snprintf(new_prefix, sizeof(new_prefix), "%s%s",
					 prefix, is_last ? TREE_SPACE : TREE_CONTINUE);
			strcat(new_prefix, "    ");
			visualize_tree_recursive(node->right, new_prefix, 1, depth + 1);
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
	printf("\n%s╔══════════════════════════════════════╗%s\n", COLOR_CYAN, COLOR_RESET);
	printf("%s║           %sAST TREE VISUALIZER%s           ║%s\n",
		   COLOR_CYAN, COLOR_WHITE, COLOR_CYAN, COLOR_RESET);
	printf("%s║  Depth: %-3d  │  Nodes: %-3d          ║%s\n",
		   COLOR_CYAN, depth, node_count, COLOR_RESET);
	printf("%s╚══════════════════════════════════════╝%s\n\n", COLOR_CYAN, COLOR_RESET);

	// Visualize the tree
	visualize_tree_recursive(root, "", 1, 0);

	printf("\n%s────────────────────────────────────────%s\n", COLOR_CYAN, COLOR_RESET);
	printf("%sLegend:%s\n", COLOR_WHITE, COLOR_RESET);
	printf("  %sNode Types:%s\n", COLOR_WHITE, COLOR_RESET);
	printf("    %s●%s COMMAND   %s●%s PIPE   %s●%s AND   %s●%s OR   %s●%s PARENTHS\n",
		   COLOR_GREEN, COLOR_RESET,
		   COLOR_BLUE, COLOR_RESET,
		   COLOR_YELLOW, COLOR_RESET,
		   COLOR_RED, COLOR_RESET,
		   COLOR_MAGENTA, COLOR_RESET);
	printf("  %sRedirections:%s\n", COLOR_WHITE, COLOR_RESET);
	printf("    %s<%s Input   %s>%s Output   %s>>%s Append   %s<<%s Heredoc\n",
		   COLOR_CYAN, COLOR_RESET,
		   COLOR_CYAN, COLOR_RESET,
		   COLOR_CYAN, COLOR_RESET,
		   COLOR_CYAN, COLOR_RESET);
	printf("%s────────────────────────────────────────%s\n\n", COLOR_CYAN, COLOR_RESET);
}

/**
 * Print a simplified flat representation of the tree
 */
void print_flat_ast(t_tree *node, int level)
{
	int i;

	if (!node)
		return;

	// Print indentation
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
 * Visualize token list with values and types
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
	printf("\n%s╔══════════════════════════════════════╗%s\n", COLOR_CYAN, COLOR_RESET);
	printf("%s║           %sTOKEN VISUALIZER%s            ║%s\n",
		   COLOR_CYAN, COLOR_WHITE, COLOR_CYAN, COLOR_RESET);
	printf("%s╚══════════════════════════════════════╝%s\n\n", COLOR_CYAN, COLOR_RESET);

	current = head;
	count = 0;

	while (current)
	{
		const char *token_color = get_token_color(current->type);
		const char *next_marker = (current->next) ? "├──" : "└──";

		printf("%s%s[%d] %s%s%s %s\"%s\"%s",
			   COLOR_CYAN,
			   next_marker,
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

	printf("\n%s────────────────────────────────────────%s\n", COLOR_CYAN, COLOR_RESET);
	printf("%sToken Legend:%s\n", COLOR_WHITE, COLOR_RESET);
	printf("  %s●%s WORD/ARG   %s●%s OPERATORS   %s●%s REDIRECTIONS   %s●%s PIPE   %s●%s R_FILE\n",
		   COLOR_WHITE, COLOR_RESET,
		   COLOR_YELLOW, COLOR_RESET,
		   COLOR_CYAN, COLOR_RESET,
		   COLOR_BLUE, COLOR_RESET,
		   COLOR_MAGENTA, COLOR_RESET);
	printf("%s────────────────────────────────────────%s\n\n", COLOR_CYAN, COLOR_RESET);
}

/**
 * Export token list to a readable format
 */
void export_tokens_to_file(t_token *head, const char *filename)
{
	FILE *file;
	t_token *current;
	int count;

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
 * Display both tokens and AST tree side by side (conceptually)
 */
void visualize_parsing_process(t_token *tokens, t_tree *ast)
{
	printf("\n%s╔══════════════════════════════════════════════════════════════╗%s\n", COLOR_CYAN, COLOR_RESET);
	printf("%s║                    %sPARSING PROCESS VISUALIZER%s                    ║%s\n",
		   COLOR_CYAN, COLOR_WHITE, COLOR_CYAN, COLOR_RESET);
	printf("%s╚══════════════════════════════════════════════════════════════╝%s\n", COLOR_CYAN, COLOR_RESET);

	printf("\n%s1. TOKENIZATION RESULT:%s\n", COLOR_YELLOW, COLOR_RESET);
	visualize_tokens(tokens);

	printf("\n%s2. AST CONSTRUCTION RESULT:%s\n", COLOR_YELLOW, COLOR_RESET);
	visualize_ast_tree(ast);

	printf("%s════════════════════════════════════════════════════════════════%s\n", COLOR_CYAN, COLOR_RESET);
}






// void print_tree(t_tree *tree)
// {
// 	int i;
// 	char *type;

// 	type = NULL;
// 	i = 0;
// 	if (!tree)
// 	{
// 		printf(BLU "EMPTY TREE\n" RESET);
// 		return;
// 	}
// 	if (tree->type == NODE_COMMAND)
// 		type = "NODE_COMMAND";
// 	else if (tree->type == NODE_PIPE)
// 		type = "NODE_PIPE";
// 	else if (tree->type == NODE_AND)
// 		type = "NODE_AND";
// 	else if (tree->type == NODE_OR)
// 		type = "NODE_OR";

// 	printf("Root Node is " ORANGE "%s :", type);
// 	while (tree->cmd[i])
// 		printf(BHGRN "{%s} " RESET, tree->cmd[i++]);
// 	printf("\nArgc : %zu\n", tree->argc);

// 	if (tree->redirs)
// 	{
// 		printf(BLU "Redirs :");
// 		while (tree->redirs)
// 		{
// 			printf("{%zu}[%d][%s] , ", tree->redirs->index, tree->redirs->type, tree->redirs->file);
// 			tree->redirs = tree->redirs->next;
// 		}
// 		printf(RESET "}\n");
// 	}
// 	if (tree->left)
// 	{
// 		printf("Left ||\n      V\n");
// 		print_tree(tree->left);
// 	}
// 	if (tree->right)
// 	{
// 		printf("Right ||\n     V\n");
// 		print_tree(tree->right);
// 	}
// }
/******************************************** start print tokens *********************************************/

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
	case NODE_PARENTHS:
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
	else if (node->type == NODE_PARENTHS)
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

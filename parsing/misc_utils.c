/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:50:58 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/16 12:03:32 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

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

int ft_syntax_err(char *str, t_token *head)
{
	ft_putstr_fd("DeepShell: syntax error near unexpected token `", 2);
	ft_putchar_fd(str[0], 2);
	ft_putendl_fd("'", 2);
	free_tokens(&head);
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

// Tree drawing characters
#define TREE_VERTICAL "│"
#define TREE_BRANCH "├──"
#define TREE_LAST "└──"
#define TREE_SPACE "    "
#define TREE_CONTINUE "│   "

/**
 * Get the string representation of a node type
 */
 const char *get_node_type_string(t_node_type type)
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
 const char *get_node_color(t_node_type type)
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
 const char *get_redir_type_string(t_token_type type)
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
 * Calculate the depth of the tree
 */
 int calculate_tree_depth(t_tree *node)
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
 int count_tree_nodes(t_tree *node)
{
	if (!node)
		return 0;

	return 1 + count_tree_nodes(node->left) + count_tree_nodes(node->right);
}

 void print_redirections(t_redir *redirs, const char *prefix, char *label)
{
	t_redir *current;
	int count;
	const char *label_color;

	if (!redirs)
		return;
	// Choose color based on redirection type
	if (!ft_strcmp(label, "Before"))
		label_color = COLOR_YELLOW;
	else if (!ft_strcmp(label, "Main"))
		label_color = COLOR_GREEN;
	else if (!ft_strcmp(label, "After"))
		label_color = COLOR_MAGENTA;
	else
		label_color = COLOR_CYAN;

	printf("%s%s┌─ %s Redirections:%s\n", prefix, label_color, label, COLOR_RESET);

	current = redirs;
	count = 0;
	while (current)
	{
		const char *next_marker = (current->next) ? "├─" : "└─";

		printf("%s%s│ %s[%d] %s%s%s %s→%s %s\"%s\"%s",
			   prefix,
			   label_color,
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
			   label_color,
			   COLOR_WHITE,
			   count,
			   count == 1 ? "" : "s",
			   COLOR_RESET);
}

/**
 * Enhanced command arguments display with better formatting
 */
 void print_command_args(char **cmd, const char *prefix)
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
 void visualize_tree_recursive(t_tree *node, const char *prefix, int is_last, int depth)
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
	has_redirections = (node->redirs_before || node->redirs || node->redirs_after);

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
		// if (node->redirs_before)
		// 	print_redirections(node->redirs_before, new_prefix, "Before");
		if (node->redirs)
			print_redirections(node->redirs, new_prefix, "Main");
		// if (node->redirs_after)
		// 	print_redirections(node->redirs_after, new_prefix, "After");

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


//  void count_tree_elements(t_tree *node, int *commands, int *redirections, int *pipes, int *operators)
// {
// 	t_redir *redir;

// 	if (!node)
// 		return;

// 	switch (node->type)
// 	{
// 	case NODE_COMMAND:
// 		(*commands)++;
// 		// Count redirections for this command
// 		redir = node->redirs_before;
// 		while (redir)
// 		{
// 			(*redirections)++;
// 			redir = redir->next;
// 		}
// 		redir = node->redirs;
// 		while (redir)
// 		{
// 			(*redirections)++;
// 			redir = redir->next;
// 		}
// 		redir = node->redirs_after;
// 		while (redir)
// 		{
// 			(*redirections)++;
// 			redir = redir->next;
// 		}
// 		break;
// 	case NODE_PIPE:
// 		(*pipes)++;
// 		break;
// 	case NODE_AND:
// 	case NODE_OR:
// 		(*operators)++;
// 		break;
// 	default:
// 		break;
// 	}

// 	count_tree_elements(node->left, commands, redirections, pipes, operators);
// 	count_tree_elements(node->right, commands, redirections, pipes, operators);
// }
/**
 * Function to get a summary of redirections in the entire tree
 */
//  void print_tree_summary(t_tree *root)
// {
// 	int total_commands = 0;
// 	int total_redirections = 0;
// 	int total_pipes = 0;
// 	int total_operators = 0;

// 	count_tree_elements(root, &total_commands, &total_redirections, &total_pipes, &total_operators);

// 	printf("%s┌─ Tree Summary:%s\n", COLOR_CYAN, COLOR_RESET);
// 	printf("%s├─ Commands: %s%d%s\n", COLOR_CYAN, COLOR_WHITE, total_commands, COLOR_RESET);
// 	printf("%s├─ Redirections: %s%d%s\n", COLOR_CYAN, COLOR_WHITE, total_redirections, COLOR_RESET);
// 	printf("%s├─ Pipes: %s%d%s\n", COLOR_CYAN, COLOR_WHITE, total_pipes, COLOR_RESET);
// 	printf("%s└─ Operators: %s%d%s\n", COLOR_CYAN, COLOR_WHITE, total_operators, COLOR_RESET);
// }

/**
 * Helper function to count different elements in the tree
 */


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
	printf("    %sBefore:%s Pre-command   %sMain:%s Command-level   %sAfter:%s Post-command\n",
		   COLOR_YELLOW, COLOR_RESET,
		   COLOR_GREEN, COLOR_RESET,
		   COLOR_MAGENTA, COLOR_RESET);
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
 * Export tree to DOT format for graphviz visualization
 */
 void export_to_dot_recursive(t_tree *node, FILE *file, int *node_id)
{
	int current_id, left_id, right_id;
	int i;

	if (!node)
		return;

	current_id = (*node_id)++;

	// Write node definition
	fprintf(file, "  node%d [label=\"%s", current_id, get_node_type_string(node->type));

	if (node->type == NODE_COMMAND && node->cmd)
	{
		fprintf(file, "\\n");
		for (i = 0; node->cmd[i] && i < 3; i++) // Limit to first 3 args for readability
		{
			fprintf(file, "%s", node->cmd[i]);
			if (node->cmd[i + 1] && i < 2)
				fprintf(file, " ");
		}
		if (node->cmd[3])
			fprintf(file, "...");
	}

	fprintf(file, "\", shape=");

	switch (node->type)
	{
	case NODE_COMMAND:
		fprintf(file, "box, style=filled, fillcolor=lightgreen");
		break;
	case NODE_PIPE:
		fprintf(file, "diamond, style=filled, fillcolor=lightblue");
		break;
	case NODE_AND:
		fprintf(file, "diamond, style=filled, fillcolor=lightyellow");
		break;
	case NODE_OR:
		fprintf(file, "diamond, style=filled, fillcolor=lightcoral");
		break;
	case NODE_PARENTHS:
		fprintf(file, "ellipse, style=filled, fillcolor=plum");
		break;
	default:
		fprintf(file, "box");
		break;
	}

	fprintf(file, "];\n");

	// Write edges to children
	if (node->left)
	{
		left_id = *node_id;
		export_to_dot_recursive(node->left, file, node_id);
		fprintf(file, "  node%d -> node%d [label=\"L\"];\n", current_id, left_id);
	}

	if (node->right)
	{
		right_id = *node_id;
		export_to_dot_recursive(node->right, file, node_id);
		fprintf(file, "  node%d -> node%d [label=\"R\"];\n", current_id, right_id);
	}
}

/**
 * Export tree to DOT format for graphviz
 */
void export_ast_to_dot(t_tree *root, const char *filename)
{
	FILE *file;
	int node_id = 0;

	file = fopen(filename, "w");
	if (!file)
	{
		printf("Error: Could not create file %s\n", filename);
		return;
	}

	fprintf(file, "digraph AST {\n");
	fprintf(file, "  rankdir=TB;\n");
	fprintf(file, "  node [fontname=\"Arial\"];\n");
	fprintf(file, "  edge [fontname=\"Arial\"];\n\n");

	if (root)
		export_to_dot_recursive(root, file, &node_id);
	else
		fprintf(file, "  empty [label=\"Empty Tree\", shape=box];\n");

	fprintf(file, "}\n");
	fclose(file);

	printf("AST exported to %s\n", filename);
	printf("To visualize: dot -Tpng %s -o ast.png\n", filename);
}
void print_tree(t_tree *tree)
{
	int i;
	char *type;

	type = NULL;
	i = 0;
	if (!tree)
	{
		printf(BLU "EMPTY TREE\n" RESET);
		return;
	}
	if (tree->type == NODE_COMMAND)
		type = "NODE_COMMAND";
	else if (tree->type == NODE_PIPE)
		type = "NODE_PIPE";
	else if (tree->type == NODE_AND)
		type = "NODE_AND";
	else if (tree->type == NODE_OR)
		type = "NODE_OR";

	printf("Root Node is " ORANGE "%s :", type);
	while (tree->cmd[i])
		printf(BHGRN "{%s} " RESET, tree->cmd[i++]);
	printf("\nArgc : %zu\n", tree->argc);

	if (tree->redirs)
	{
		printf(BLU "Redirs :");
		while (tree->redirs)
		{
			printf("{%zu}[%d][%s] , ", tree->redirs->index, tree->redirs->type, tree->redirs->file);
			tree->redirs = tree->redirs->next;
		}
		printf(RESET "}\n");
	}
	if (tree->left)
	{
		printf("Left ||\n      V\n");
		print_tree(tree->left);
	}
	if (tree->right)
	{
		printf("Right ||\n     V\n");
		print_tree(tree->right);
	}
}

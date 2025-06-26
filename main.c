/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:05:35 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/26 18:53:26 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

/**
 * @brief Creates a tree for content inside parentheses
 * @param ast Root node
 * @param tokens Tokenizer Tokens
 * @param flag Navigation flag for search
 */
void create_pseudotree(t_tree **ast, t_token **tokens)
{
	t_token *parentheses;

	if (!tokens || !*tokens)
		return;
	refresh_block(tokens,0);
	parentheses = find_Parentheses(*tokens);
	if (parentheses)
	{
		*ast = create_block(&parentheses, 1, block_identifier(parentheses));
		parentheses->position = -1;
		// printf("Created a Parentheses Node\n");
		if (parentheses->next)
			create_one_tree(&(*ast)->left, &parentheses->next);
	}
	else
	{
		// printf("No parentheses Found ! creating a simple node\n");
		*ast = create_block(tokens, count_cmd_args(*tokens), block_identifier(*tokens));
	}
}
// int create_p_block(t_token **head, int count, int type)
// {
// 	t_token * current;

// 	current = *head;
// 	while()
// 	return 1;
// }

t_token *get_root(t_token *toks)
{
	t_token	*curr;
	int	pipe  = 0;
	int	and_or = 0;
	int	parenthese = 0;
	t_token *r = NULL;
	curr = toks;
	while(curr)
	{
		if (curr->type == TOKEN_PAREN_LEFT)
			parenthese ++;
		else if (curr->type == TOKEN_PAREN_RIGHT)
			parenthese--;
		if ((curr->type == TOKEN_AND || curr->type == TOKEN_OR) && !parenthese)
		{
			r = curr;
			and_or = 1;
		}
		if (curr->type == TOKEN_PIPE && !and_or && !parenthese)
		{
			r = curr;
			pipe = 1;
		}
		curr = curr->next;
	}
	return (r);
}

t_token	*make_left(t_token *toks, t_token *root)
{
	t_token *curr = toks;
	while (curr && curr!=root)
		curr = curr->next;
	curr->prev->next = NULL;
	return (toks);
}

t_tree *create_block_2(t_token *tok)
{
	t_tree *node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	printf("%s\n", tok->value);
	return (NULL);
}
t_tree *create_tree(t_token *tokens)
{
	t_token	*root;
	t_tree	*node;
	t_token	*l, *r;
	root = get_root(tokens);
	if (!root)
		return create_block(&tokens, count_cmd_args(tokens),NODE_COMMAND);
	printf("root ; %d\n", root->type);
	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	ft_bzero(node, sizeof(t_tree));
	node->type = block_identifier(root);
	r = root->next;
	l = make_left(tokens, root);
	free(root->value);
	free(root);
	node->left = create_tree(l);
	node->right = create_tree(r);
	return node;
}

void f()
{
	system("leaks -q -- minishell");
}

int main(int argc, char **argv, char **envp)
{
	t_shell shell;
	t_stash stash;

	// atexit(f);
	(void)argc, (void)argv;
	rl_catch_signals = 0;
	stash.status = 0;
	stash.heredoc_interrupted = 0;
	init_shell(&shell);
	build_env(&shell.env_list, envp);
	while (1)
	{
		g_sigint_received = 0; // Reset flag at the start of each loop
		stash.heredoc_interrupted = 0;
		setup_signals_prompt(); // Setup signals for the main prompt
		disable_echoctl(&stash);
		shell.line = readline("L33tShell-N.Y$ ");
		add_history(shell.line);
		if (!shell.line)
		{
			free_tokens(&shell.tokens);
			free_all_tracked();
			exit(stash.status);
		}
		if (!shell.line || ft_str_isspace(shell.line) || !lexer(&shell, 0) || !parser(shell))
		{
			free(shell.line);
			free_tokens(&shell.tokens);
			continue;
		}
		// visualize_tokens(shell.tokens);
		// shell.ast = create_tree(shell.tokens);
		create_one_tree(&shell.ast, &shell.tokens);
		visualize_ast_tree(shell.ast);
		// print_tree(shell.ast);
		// check_heredoc_limit(&shell,shell.ast); // ? Changed the freeing to include clear memory.
		// setup_signals_heredoc();
		// manage_heredocs(shell.ast, &stash);
		// if (!stash.heredoc_interrupted)
		// 	execute_ast(shell.ast, &shell.env_list, &stash);
		// else
		// {
		// 	clear_memory(&shell);
		// 	continue;
		// }
		// if (ft_strnstr(shell.line, "leaks", ft_strlen(shell.line)))
		// 	break;
		clear_memory(&shell);
	}
	// clear_memory(&shell);
	return (0);
}

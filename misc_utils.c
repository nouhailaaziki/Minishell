/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:50:58 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/08 09:19:50 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

void	print_redirs(t_redir *redir)
{
	while (redir)
	{
		printf(BLU "Redir type: ");
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
		printf(", file: %s\n" RESET, redir->file);
		redir = redir->next;
	}
}


void print_tokens(t_var **head)
{
	t_var *tmp;
	// char *tiipe;

	if(!head || !*head)
	{
		puts("No keys to print");
		return;
	}
	tmp = *head;
	while (tmp)
	{
	// 	if (tmp->type == TOKEN_OR)
	// 		tiipe = "OR";
	// 	else if (tmp->type == TOKEN_AND)
	// 		tiipe = "AND";
	// 	else if (tmp->type == REDIR_HEREDOC)
	// 		tiipe = "REDIR_HEREDOC";
	// 	else if (tmp->type == REDIR_APPEND)
	// 		tiipe = "REDIR_APPEND";
	// 	else if (tmp->type == REDIR_IN)
	// 		tiipe = "REDIR_IN";
	// 	else if (tmp->type == REDIR_OUT)
	// 		tiipe = "REDIR_OUT";
	// 	else if (tmp->type == TOKEN_PIPE)
	// 		tiipe = "PIPE";
	// 	else if (tmp->type == R_FILE)
	// 		tiipe = "R_FILE";
	// 	else if (tmp->type == TOKEN_ARG)
	// 		tiipe = "ARGUMENT";
	// 	else if (tmp->type == TOKEN_PAREN)
	// 		tiipe = "PARENTHESE_BLOCK";
	// 	else
	// 		tiipe = "WORD";
			// printf(GRN "value : {%s}, type? : {%s}->{%d} , position : <%d>\n" RESET, (tmp)->value, tiipe, (tmp)->type, tmp->position);

		printf(GRN "key : {%s}, expandable? : {%s} , key_len : <%d> value_len : <%d>\n" RESET, (tmp)->key, (tmp)->expandable != 39 ? "YES" : "NO" , tmp->key_len , tmp->value_len);
		tmp = (tmp)->next;
	}
}

// t_token *get_reds(t_token *tok)
// {
// 	int expectations = 1;
// 	t_token *curr = tok->next;

// 	while (curr && expectations)
// 	{
// 		if (curr->type == TOKEN_PAREN_LEFT)
// 			expectations++;
// 		else if (curr->type == TOKEN_PAREN_RIGHT)
// 			expectations--;
// 		curr = curr->next;
// 	}
// 	return curr;
// }
// t_tree *expand_block(t_token *token)
// {
// 	t_tree *root = malloc(sizeof(t_tree));
// 	t_token *block = NULL;
// 	t_token *reds = NULL;
// 	if (!root)
// 		return (NULL);
// 	printf("here\n");
// 	ft_bzero(root, sizeof(t_tree));
// 	root->type = NODE_PARENTHESES;
// 	if (token->prev)
// 		token->prev->next = token->next;
// 	// free(token->value);
// 	// free(token);
// 	block = token->next;
// 	reds = get_reds(token);
// 	printf("%s\n", reds->value);
// 	if (reds->prev && reds->prev->prev)
// 		reds->prev->prev->next = NULL;
// 	// free(reds->prev->value);
// 	// free(reds->prev);
// 	root->left = create_tree(block);
// 	root->redirs = redir_list_maker(&reds);
// 	root->right = NULL;
// 	return (root);
// }
// t_token *get_root(t_token *toks)
// {
// 	t_token *curr;
// 	int pipe = 0;
// 	int and_or = 0;
// 	int parenthese = 0;
// 	t_token *r = NULL;
// 	curr = toks;
// 	while (curr)
// 	{
// 		if (curr->type == TOKEN_PAREN_LEFT)
// 			parenthese++;
// 		else if (curr->type == TOKEN_PAREN_RIGHT)
// 			parenthese--;
// 		if ((curr->type == TOKEN_AND || curr->type == TOKEN_OR) && !parenthese)
// 		{
// 			r = curr;
// 			and_or = 1;
// 		}
// 		if (curr->type == TOKEN_PIPE && !and_or && !parenthese)
// 		{
// 			r = curr;
// 			pipe = 1;
// 		}
// 		curr = curr->next;
// 	}
// 	return (r);
// }
// t_token *make_left(t_token *toks, t_token *root)
// {
// 	t_token *curr = toks;
// 	while (curr && curr != root)
// 		curr = curr->next;
// 	curr->prev->next = NULL;
// 	return (toks);
// }
// t_tree *create_block_2(t_token *tok)
// {
// 	t_tree *node = malloc(sizeof(t_tree));
// 	if (!node)
// 		return (NULL);
// 	printf("%s\n", tok->value);
// 	return (NULL);
// }
// t_tree *create_tree(t_token *tokens)
// {
// 	t_token *root;
// 	t_tree *node;
// 	t_token *l, *r;
// 	root = get_root(tokens);
// 	if (!root)
// 		return create_block(&tokens, count_cmd_args(tokens), NODE_COMMAND);
// 	printf("root ; %d\n", root->type);
// 	node = malloc(sizeof(t_tree));
// 	if (!node)
// 		return (NULL);
// 	ft_bzero(node, sizeof(t_tree));
// 	node->type = block_identifier(root);
// 	r = root->next;
// 	l = make_left(tokens, root);
// 	free(root->value);
// 	free(root);
// 	node->left = create_tree(l);
// 	node->right = create_tree(r);
// 	return node;
// }

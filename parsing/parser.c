/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:10:04 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/03 08:55:16 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

t_redir	*new_redir(t_redir_type type, char *file)
{
	t_redir *r;
	
	r = nalloc(sizeof(t_redir));
	r->index = 0;
	r->type = type;
	r->file = na_strdup(file);
	r->fd = -1;
	r->flag = 0;
	r->next = NULL;
	return (r);
}

t_tree	*new_command_node(char **cmd, t_redir *redir)
{
	t_tree *n;
	
	n = nalloc(sizeof(t_tree));
	n->type = NODE_COMMAND;
	n->cmd = cmd;
	n->redirs = redir;
	n->redirs_before = NULL;
	n->redirs_after = NULL;
	n->is_ambiguous = 0;
	n->left = NULL;
	n->right = NULL;
	return (n);
}

t_tree	*new_pipe_node(t_tree *left, t_tree *right)
{
	t_tree *n;
	
	n = nalloc(sizeof(t_tree));
	n->type = NODE_PIPE;
	n->cmd = NULL;
	n->redirs = NULL;
	n->redirs_before = NULL;
	n->redirs_after = NULL;
	n->is_ambiguous = 0;
	n->left = left;
	n->right = right;
	return (n);
}

char	**split_args(char *str)
{
	int i;
	char *tok;
	char **res;

	i = 0;
	res = nalloc(sizeof(char *) * 10);
	tok = strtok(str, " ");
	while (tok)
	{
		res[i++] = na_strdup(tok);
		tok = strtok(NULL, " ");
	}
	res[i] = NULL;
	return (res);
}
t_redir *reverse_redir_list(t_redir *head)
{
	t_redir *prev;
	t_redir *current;
	t_redir *next;

	prev = NULL;
	current = head;
	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	return (prev);
}

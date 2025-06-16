/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:08:57 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/16 08:35:13 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

 void free_tree(t_tree **ast)
{
	int count;

	count = 0;
	if(!(*ast))
		return;
	while ((*ast)->redirs)
	{
		free((*ast)->redirs);
		(*ast)->redirs = (*ast)->redirs->next;
	}
	(*ast)->redirs  = NULL;
	while ((*ast)->cmd[count] && (*ast)->cmd[count] != NULL)
	{
		free((*ast)->cmd[count]);
		(*ast)->cmd[count] = NULL;
		count++;
	}
	free((*ast)->cmd[count]);
	(*ast)->cmd[count] = NULL;
	if ((*ast)->left)
			free_tree((*ast)->left);
	if ((*ast)->left)
		free_tree((*ast)->right);
	free((*ast));
	(*ast) = NULL;
}

void clear_memory(t_shell *shell)
{
	if(shell->ast)
		free_tree(&shell->ast);
	free_tokens(&shell->tokens);
	free(shell->line);
}
 void free_tokens(t_token **head)
{
	t_token *tmp;

	tmp = NULL;
	while ((*head))
	{
		tmp = (*head);
		free(tmp->value);
		free(tmp);
		(*head) = (*head)->next;
	}
}

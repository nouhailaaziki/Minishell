/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:08:57 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/13 16:15:02 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

 void free_tree(t_tree **ast)
{
	int count;

	count = 0;
	if(!(*ast))
		return;
	while ((*ast)->cmd && (*ast)->cmd[count] != NULL)
	{
		ft_printf("Freeing %s \n", (*ast)->cmd[count]);
		free((*ast)->cmd[count]);
		count++;
	}
	while ((*ast)->redirs)
	{
		free((*ast)->redirs);
		(*ast)->redirs = (*ast)->redirs->next;
	}
	free_tree(&((*ast)->right));
	free_tree(&((*ast)->left));
	free((*ast));
}

void clear_memory(t_tree **ast, t_token **tokens, char *line)
{
	free_tree(ast);
	free_tokens(tokens);
	free(line);
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

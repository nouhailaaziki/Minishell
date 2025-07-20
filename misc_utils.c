/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:50:58 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/20 09:43:42 by yrhandou         ###   ########.fr       */
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

void	print_tokens(t_var **head)
{
	t_var	*tmp;

	if (!head || !*head)
	{
		puts("No keys to print");
		return ;
	}
	tmp = *head;
	while (tmp)
	{
		printf(GRN "key : {%s}, expandable? : {%s} , key_len : <%d> value_len : <%d>\n" RESET, (tmp)->key, (tmp)->expandable != 39 ? "YES" : "NO", tmp->key_len, tmp->value_len);
		tmp = (tmp)->next;
	}
}

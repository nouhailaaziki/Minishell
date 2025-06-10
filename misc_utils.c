/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:50:58 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/10 16:00:19 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

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
	ft_putchar_fd(str[0], 2);
	ft_putendl_fd("'", 2);
	free_tokens(head);
	return 0;
}
// void free_tokens(t_token **head)
// {
// 	t_token *tmp;
// 	t_token *next;
// 	// ft_printf(MAG "Freeing Tokens !-------\n"RESET);
// 	tmp = *head;
// 	while (tmp)
// 	{
// 		next = tmp->next;
// 		free(tmp->value);
// 		free(tmp);
// 		(tmp) = next;
// 	}
// }

void free_tokens(t_token **head)
{
	t_token *tmp;
	// ft_printf(MAG "Freeing Tokens !-------\n"RESET);
	while ((*head))
	{
		tmp = (*head);
		free(tmp->value);
		free(tmp);
		(*head) = (*head)->next;
	}
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

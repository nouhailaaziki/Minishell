/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 08:08:42 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/09 17:29:28 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

int redir_identifier(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (REDIR_APPEND);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (REDIR_HEREDOC);
	if (str[0] == '<')
		return (REDIR_OUT);
	if (str[0] == '>')
		return (REDIR_IN);
	return (0);
}

void quote_expander(t_token **head)
{
	t_token *current;
	int position;
	int i;
	char quote;
	char *expanded_token;
	i = 0;
	position = 0;
	current = *head;
	while (current)
	{
		if (ft_strchr(current->value, '\"') == NULL && ft_strchr(current->value, '\'') == NULL)
		{
			current = current->next;
			continue;
		}
		expanded_token = ft_calloc(ft_strlen(current->value) + 1, sizeof(char));
		if (!expanded_token)
			return free_tokens(head), ft_putendl_fd("MALLOC FAILURE", 2);
		while (current->value[i])
		{
			quote = ft_isquote(current->value[i]);
			if (quote != '\0')
			{
				i++;
				while (current->value[i] && current->value[i] != quote)
					expanded_token[position++] = current->value[i++];
				if (current->value[i] == quote)
					i++;
			}
			else
				expanded_token[position++] = current->value[i++];
		}
		if (expanded_token)
		{
			free(current->value);
			current->value = expanded_token;
		}
		current = current->next;
	}
}
void advanced_token_lexer(t_token **head)
{
	t_token *current;

	current = *head;
	while (current && current->next)
	{
		if (current->type == TOKEN_REDIR)
		{
			current->type = redir_identifier(current->value);
			current->next->type = R_FILE;
		}
		if ((current->type == TOKEN_WORD || current->type == TOKEN_ARG || current->type == R_FILE) && \
			(current->next->type == TOKEN_WORD))
			current->next->type = TOKEN_ARG;
		current = current->next;
	}
}
int parser(t_token **head)
{
	t_token *current;

	current = *head;
	if (!current)
		return 0;
	if (ft_is_bonus_operator(current->value) || (current->type == TOKEN_PIPE))
		return ft_syntax_err(current->value, head);
	while (current)
	{
		if (ft_is_operator(current->value) && !current->next)
			return ft_syntax_err(current->value, head);
		if (ft_is_redir(current->value) && ft_isparentheses(current->next->value))
			return ft_syntax_err(current->value, head);
		current = current->next;
	}
	advanced_token_lexer(head);
	// quote_expander(head);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 08:08:42 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/07 21:02:41 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

void	parentheses_lexer(t_token **head)
{
	t_token	*current;

	current = *head;
	if (current->type == TOKEN_PAREN && current->value[0] == '(')
		current->type = TOKEN_PAREN_LEFT;
	else if (current->type == TOKEN_PAREN && current->value[0] == ')')
		current->type = TOKEN_PAREN_RIGHT;
}

void	redir_lexer(t_token **head)
{
	t_token	*current;

	current = *head;
	current->type = redir_identifier(current->value);
	if (current->next)
		current->next->type = R_FILE;
}

void	cmd_lexer(t_token **head)
{
	t_token		*current;
	int			cmd_found;

	cmd_found = 0;
	current = *head;
	while (current)
	{
		if (ft_is_operator(current->value))
			cmd_found = 0;
		if (current->type == TOKEN_WORD)
		{
			if (!cmd_found && (!current->prev
					|| ft_is_operator(current->prev->value)
					|| current->prev->type == R_FILE
					|| current->prev->type == TOKEN_PAREN_LEFT))
			{
				current->type = TOKEN_CMD;
				cmd_found = 1;
			}
			else if (cmd_found)
				current->type = TOKEN_ARG;
		}
		current = current->next;
	}
}

void	advanced_token_lexer(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current)
	{
		if (current->type == TOKEN_REDIR)
			redir_lexer(&current);
		if (current->type == TOKEN_PAREN)
			parentheses_lexer(&current);
		current = current->next;
	}
	cmd_lexer(head);
}

/**
 * @brief Checks the tokens created with the tokenizer for syntax errors
 * @param shell shell data
 */
int	parser(t_shell *shell)
{
	t_token	*current;

	if (!shell->tokens)
		return (0);
	current = shell->tokens;
	if (!simple_syntax_err(shell))
		return (0);
	advanced_token_lexer(&shell->tokens);
	if (!advanced_syntax_err(shell))
		return (0);
	while (current)
	{
		if (ft_is_operator(current->value) && \
		(!current->prev || current->prev->type == TOKEN_PAREN_LEFT))
			return (ft_syntax_err(current->value, shell));
		current = current->next;
	}
	if (!handle_parentheses(shell))
		return (0);
	return (1);
}

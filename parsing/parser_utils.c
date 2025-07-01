/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 08:08:42 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/29 09:57:19 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

void	quote_expander(t_token **head)
{
	t_token	*current;
	int		position;
	int		i;
	char	quote;
	char	*expanded_token;

	i = 0;
	position = 0;
	current = *head;
	while (current)
	{
		if (ft_strchr(current->value, '\"') == NULL && \
		ft_strchr(current->value, '\'') == NULL)
		{
			current = current->next;
			continue ;
		}
		expanded_token = ft_calloc(ft_strlen(current->value) + 1, sizeof(char));
		if (!expanded_token)
			return (free_tokens(head), ft_putendl_fd("MALLOC FAILURE", 2));
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
	int		in_paren;

	current = *head;
	in_paren = 0;
	while (current)
	{
		if (current->type == TOKEN_PAREN && current->value[0] == '(')
			current->type = TOKEN_PAREN_LEFT;
		if (current->type == TOKEN_PAREN && current->value[0] == ')')
			current->type = TOKEN_PAREN_RIGHT;
		current = current->next;
	}
}

void	advanced_token_lexer(t_token **head)
{
	t_token	*current;
	int		in_paren;

	in_paren = 0;
	current = *head;
	while (current)
	{
		if (current->type == TOKEN_PAREN)
			parentheses_lexer(&current);
		if (current->type == TOKEN_REDIR && current->next)
		{
			current->type = redir_identifier(current->value);
			current->next->type = R_FILE;
		}
		if ((current->type == TOKEN_CMD || current->type == TOKEN_ARG || \
			current->type == R_FILE) \
		&& (current->next && current->next->type == TOKEN_CMD))
			current->next->type = TOKEN_ARG;
		current = current->next;
	}
}

/**
 * @brief Checks the tokens created with the tokenizer for syntax errors
 * @param shell shell data
 */
int	parser(t_shell shell)
{
	t_token	*current;

	if (!shell.tokens)
		return (0);
	current = shell.tokens;
	if (!simple_syntax_err(shell.tokens))
		return (0);
	advanced_token_lexer(&shell.tokens);
	if (!advanced_syntax_err(shell.tokens))
		return (0);
	while (current)
	{
		if (ft_is_operator(current->value) && \
		(!current->prev || current->prev->type == TOKEN_PAREN_LEFT))
			return (ft_syntax_err(current->value));
		current = current->next;
	}
	if (!handle_parentheses(shell.tokens))
		return (0);
	return (1);
}

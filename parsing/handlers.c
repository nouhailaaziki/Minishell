/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:09:54 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/26 09:57:51 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

/**
 * @brief Handle quote expansion during tokenization
 * @param str string to check.
 * @param c quote type
 * @return Length of skipped string
 */
// TODO : Something is off here...
int	handle_quotes(char *str, char c)
{
	int		i;
	char	commander;
	int		in_quote;

	1 && (i = 1, in_quote = 1, commander = c);
	while (str[i] != '\0')
	{
		if ((ft_is_operator(&str[i]) || ft_is_redir(&str[i])) && !in_quote)
			break ;
		if (str[i] == commander && in_quote)
			in_quote = 0;
		else if (ft_isquote(str[i]) && !in_quote)
		{
			if (str[i] != commander)
				commander = str[i];
			in_quote = 1;
		}
		if ((str[i] == ' ' || \
			ft_isparentheses(&str[i])) && !in_quote)
			break ;
		i++;
	}
	if (in_quote)
		return (0);
	return (i);
}

/**
 * @brief check if the parenthese count is correct
 * @param head the Node to check for
 * @return Retuns 1 on success , and 0 on Failure
 */
int	parentheses_counter_v2(t_token *head)
{
	int		parentheses;
	t_token	*current;

	parentheses = 0;
	current = head;
	while (current)
	{
		if (current->type == TOKEN_PAREN_LEFT)
			parentheses += 1;
		else if (current->type == TOKEN_PAREN_RIGHT)
			parentheses -= 1;
		current = current->next;
	}
	if (parentheses != 0)
		return (0);
	return (1);
}

int	check_successor(t_token *head)
{
	t_token	*current;

	if (!head)
		return (1);
	current = head;
	while (current && current->type != TOKEN_AND && \
		current->type != TOKEN_OR && current->type != TOKEN_PIPE)
	{
		if (current->type == TOKEN_ARG || current->type == TOKEN_CMD || \
			current->type == TOKEN_PAREN_LEFT)
			return (0);
		current = current->next;
	}
	return (1);
}

int	check_predecessor(t_token *head)
{
	t_token	*current;

	if (!head)
		return (1);
	current = head;
	while (current && current->type != TOKEN_AND && \
		current->type != TOKEN_OR && current->type != TOKEN_PIPE)
	{
		if (current->type == TOKEN_ARG || current->type == TOKEN_CMD || \
			current->type == TOKEN_PAREN_RIGHT || current->type == R_FILE)
			return (0);
		current = current->prev;
	}
	return (1);
}

int	ft_syntax_analyzer(char *str)
{
	int	i;
	int	set;

	i = 0;
	while (str[i] && !ft_isparentheses(&str[i]) && (!ft_is_operator(&str[i]) && \
	!ft_is_redir(&str[i])) && !ft_issubspace(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			set = handle_quotes(&str[i], str[i]);
			if (!set)
				return (0);
			i += set;
			break ;
		}
		i++;
	}
	return (i);
}

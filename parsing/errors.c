/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 08:25:19 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/21 13:54:57 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

int	ft_syntax_err(t_shell *shell)
{
	ft_putstr_fd("L33tShell: syntax error near unexpected token \n", 2);
	shell->stash.status = 258;
	return (0);
}

int	handle_parentheses(t_shell *shell)
{
	t_token	*current;

	current = shell->tokens;
	if (!parentheses_counter_v2(current))
		return (ft_syntax_err(shell));
	while (current)
	{
		if (current->type == TOKEN_PAREN_LEFT && (!current->next || \
			current->next->type == TOKEN_PAREN_RIGHT || \
			!check_predecessor(current->prev)))
			return (ft_syntax_err(shell));
		if (current->type == TOKEN_PAREN_RIGHT && (!current->prev || \
			!check_successor(current->next)))
			return (ft_syntax_err(shell));
		current = current->next;
	}
	return (1);
}

int	advanced_syntax_err(t_shell *shell)
{
	t_token	*current;

	current = shell->tokens;
	while (current)
	{
		if (ft_is_operator(current->value) && (!current->next || \
			ft_is_operator(current->next->value)))
			return (ft_syntax_err(shell));
		if (ft_is_operator(current->value) && (!current->next || \
			current->next->type == TOKEN_PAREN_RIGHT))
			return (ft_syntax_err(shell));
		current = current->next;
	}
	return (1);
}

int	simple_syntax_err(t_shell *shell)
{
	t_token	*current;

	current = shell->tokens;
	if (ft_is_operator(current->value))
		return (ft_syntax_err(shell));
	while (current)
	{
		if (current->type == TOKEN_REDIR
			&& (!current->next || current->next->type == TOKEN_PAREN
				|| ft_is_operator(current->next->value)
				|| current->next->type == TOKEN_REDIR))
			return (ft_syntax_err(shell));
		current = current->next;
	}
	return (1);
}

int	is_empty_values(t_var *keys)
{
	if (!keys)
		return (0);
	while (keys)
	{
		if (keys->value != NULL)
			return (0);
		keys = keys->next;
	}
	return (1);
}

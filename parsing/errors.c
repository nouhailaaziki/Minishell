/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 08:25:19 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/01 10:11:29 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

int ft_syntax_err(char *str, t_shell *shell)
{
	ft_putstr_fd("DeepShell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("'", 2);
	return (0);
}

int	handle_parentheses(t_token *head)
{
	t_token	*current;

	current = head;
	if (!parentheses_counter_v2(current))
		return (ft_syntax_err(current->value));
	while (current)
	{
		if (current->type == TOKEN_PAREN_LEFT && (!current->next || \
			current->next->type == TOKEN_PAREN_RIGHT || \
			!check_predecessor(current->prev)))
			return (ft_syntax_err(current->value));
		if (current->type == TOKEN_PAREN_RIGHT && (!current->prev || \
			!check_successor(current->next)))
			return (ft_syntax_err(current->value));
		current = current->next;
	}
	return (1);
}

int	advanced_syntax_err(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		if (ft_is_operator(current->value) && (!current->next || \
			ft_is_operator(current->next->value)))
			return (ft_syntax_err(current->value));
		if (ft_is_operator(current->value) && (!current->next || \
			current->next->type == TOKEN_PAREN_RIGHT))
			return (ft_syntax_err(current->value));
		current = current->next;
	}
	return (1);
}

int	simple_syntax_err(t_token *head)
{
	t_token	*current;

	current = head;
	if (ft_is_operator(current->value))
		return (ft_syntax_err(current->value));
	while (current)
	{
		if (current->type == TOKEN_REDIR
			&& (!current->next || current->next->type == TOKEN_PAREN
				|| ft_is_operator(current->next->value)
				|| current->next->type == TOKEN_REDIR))
			return (ft_syntax_err(current->value, &shell->stash));
		current = current->next;
	}
	return (1);
}

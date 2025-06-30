/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 08:25:19 by yrhandou          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/06/28 16:58:25 by yrhandou         ###   ########.fr       */
=======
/*   Updated: 2025/06/30 11:28:45 by yrhandou         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

int	ft_syntax_err(char *str,t_stash *stash)
{
	ft_putstr_fd("DeepShell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("'", 2);
	stash->status = 258;
	dprintf(2, "EXIT STATUS %d\n", stash->status);
	return (0);
}

int	handle_parentheses(t_shell *shell)
{
	t_token	*current;

	current = shell->tokens;
	if (!parentheses_counter_v2(current))
		return (ft_syntax_err(current->value, &shell->stash));
	while (current)
	{
		if (current->type == TOKEN_PAREN_LEFT
			&& (!current->next
				|| current->next->type == TOKEN_PAREN_RIGHT
				|| !check_predecessor(current->prev)))
			return (ft_syntax_err(current->value, &shell->stash));
		if (current->type == TOKEN_PAREN_RIGHT
			&& (!current->prev || !check_successor(current->next)))
			return (ft_syntax_err(current->value, &shell->stash));
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
		if (ft_is_operator(current->value)
			&& (!current->next || ft_is_operator(current->next->value)))
			return (ft_syntax_err(current->value, &shell->stash));
		if (ft_is_operator(current->value)
		&& (!current->next || current->next->type == TOKEN_PAREN_RIGHT))
			return (ft_syntax_err(current->value, &shell->stash));
		current = current->next;
	}
	return (1);
}

int	simple_syntax_err(t_shell *shell)
{
	t_token	*current;

	current = shell->tokens;
	if (ft_is_operator(current->value))
		return (ft_syntax_err(current->value, &shell->stash));
	while (current)
	{
<<<<<<< Updated upstream
		if (current->type == TOKEN_REDIR && (!current->next || \
			current->next->type == TOKEN_PAREN))
			return (ft_syntax_err(current->value));
=======
		if (current->type == TOKEN_REDIR
			&& (!current->next || current->next->type == TOKEN_PAREN
				|| ft_is_operator(current->next->value)
				|| current->next->type == TOKEN_REDIR))
			return (ft_syntax_err(current->value, &shell->stash));
>>>>>>> Stashed changes
		current = current->next;
	}
	return (1);
}

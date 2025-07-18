/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:19:50 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/12 17:05:35 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

int	token_lexer(char *str)
{
	int	operator_length;

	operator_length = ft_is_operator(str);
	if (operator_length == 2)
	{
		if (str[0] == '|')
			return (TOKEN_OR);
		if (str[0] == '&')
			return (TOKEN_AND);
	}
	else if (operator_length == 1)
	{
		if (str[0] == '|')
			return (TOKEN_PIPE);
	}
	if (str[0] == '<' || str[0] == '>')
		return (TOKEN_REDIR);
	else if (ft_isparentheses(&str[0]))
		return (TOKEN_PAREN);
	return ((TOKEN_WORD));
}

void	link_token(t_token **head, t_token *node)
{
	t_token	*tmp;

	if (!node)
	{
		ft_putendl_fd("Error Token is Empty\n", 2);
		return ;
	}
	if (!head || !*head)
	{
		*head = node;
		node->next = NULL;
		node->prev = NULL;
		node->position = 0;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->position = tmp->position + 1;
	node->next = NULL;
	node->prev = tmp;
}

t_token	*new_token(char *value, int type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (value)
	{
		token->value = ft_strdup(value);
		if (!token->value)
			return (free(token), ft_putendl_fd("Strdup Failure\n", 2), NULL);
	}
	else
		return (free(token), ft_putendl_fd("Malloc Error\n", 2), NULL);
	token->next = NULL;
	token->prev = NULL;
	token->position = -1;
	return (token);
}

int	lexer(t_shell *shell)
{
	int		i;
	int		token_len;
	int		position;
	char	*sub_str;

	i = 0;
	while (shell->line[i])
	{
		i += skip_spaces(&shell->line[i]);
		position = i;
		token_len = token_lookup(&shell->line[i]);
		if (!token_len)
			return (ft_syntax_err(shell));
		sub_str = ft_substr(shell->line, position, token_len);
		link_token(&shell->tokens, new_token(sub_str, (token_lexer \
			(&shell->line[position]))));
		free(sub_str);
		i += token_len;
		if (ft_str_isspace(&shell->line[i]))
			break ;
	}
	return (1);
}

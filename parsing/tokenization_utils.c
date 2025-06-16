/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:19:50 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/15 18:37:51 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

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
		if (str[0] == '<' || str[0] == '>')
			return (TOKEN_REDIR);
	}
	else if (operator_length == 1)
	{
		if (str[0] == '|')
			return (TOKEN_PIPE);
		if (str[0] == '<' || str[0] == '>')
			return (TOKEN_REDIR);
	}
	else if(str[0] == '(')
		return (TOKEN_PAREN);
	return ((TOKEN_WORD));
}

int	ft_special_case(char *str, int type)
{
	int	new_type;

	new_type = token_lexer(&str[skip_spaces(str)]);
	if ((type != TOKEN_REDIR) && (new_type == TOKEN_REDIR))
		return (1);
	return (0);
}
int	operator_len(char *str) //returns the length of the operator on success
{
	int		i;
	int		len;
	int		type;

	i = 0;
	len = ft_is_operator(&str[i]);
	if(!len)
		return (0);
	type = token_lexer(&str[i]);
	i += len; // if(!str[i]) 	return 0;
	len = i;
	while(str[len])
	{
		if((ft_special_case(&str[len],type)))
			break;
		else if (ft_before_x(&str[len], ft_is_operator))
			return 0;
		else if (!ft_isspace(str[len]))
			break;
		len++;
	}
	return (i);
}

void	link_token(t_token **head, t_token *node)
{
	t_token	*tmp;

	tmp = *head;
	if (!*head)
	{
		*head = node;
		node->next = NULL;
		node->prev = NULL;
		node->position = 0;
		return ;
	}
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
	token->value = value;
	token->next = NULL;
	token->prev = NULL;
	token->position = -1;
	return (token);
}

int	lexer(t_shell *shell, int status_flag)
{
	int	i;
	int	token_len;
	int	position;

	i = 0;
	while (shell->line[i])
	{
		i += skip_spaces(&shell->line[i]);
		position = i;
		token_len = count_chars(&shell->line[i]);
		if (!token_len)
			token_len = operator_len((char *)&shell->line[i]);
		if (!token_len)
			return (ft_syntax_err(&shell->line[i], (shell)->tokens));
		if(status_flag)
			break;
		link_token(&shell->tokens, new_token(ft_substr(shell->line, position, token_len), \
		(token_lexer(&shell->line[position]))));
		i += token_len;
		position = i;
		if (ft_str_isspace(&shell->line[i]))
			break ;
	}
	return (1);
}

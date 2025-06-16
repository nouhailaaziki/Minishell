/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 08:08:42 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/15 18:36:56 by yrhandou         ###   ########.fr       */
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
int parentheses_lexer(char * p_string)
{
	int i;
	t_shell dummy;
	int count;

	count = 0;
	if(!p_string)
	{
		printf(RED"FATAL ERROR 0\n"RESET);
		return 0;
	}
	i = 1;
	dummy.line = &p_string[i];
	while (p_string[i] != ')' && p_string[i+1] != '\0')
	{
		i++;
		count++;
	}
	printf("len inside () is : %d\n ",count);
	if(!lexer(&dummy, 1))
		return ft_syntax_analyzer(p_string);
	return 1;
}


int advanced_token_lexer(t_token **head)
{
	t_token *current;

	current = *head;
	while (current && current->next)
	{
		if(current->value[0] == '(')
			current->type = TOKEN_PAREN;
		if (current->type == TOKEN_PAREN && !parentheses_lexer(current->value))
			return 0;
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
	return 1;
}
int parser(t_shell shell)
{
	t_token	*current;

	if (!shell.tokens)
		return 0;
	current = shell.tokens;
	if (ft_is_bonus_operator(current->value) || (current->type == TOKEN_PIPE))
		return ft_syntax_err(current->value, shell.tokens);
	while (current)
	{
		if (ft_is_operator(current->value) && !current->next)
			return ft_syntax_err(current->value, shell.tokens);
		if (ft_is_redir(current->value) && ft_isparentheses(current->next->value))
			return ft_syntax_err(current->value, shell.tokens);
		current = current->next;
	}
	// quote_expander(head);
	if(!advanced_token_lexer(&shell.tokens))
		return ft_syntax_err(current->value, shell.tokens);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 08:33:00 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/12 20:44:12 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

/**
 * @brief checks the type of token to make
 * @param line
 * @return the length of the tokens
 */
int	token_lookup(char *line)
{
	int	token_len;

	token_len = count_chars(line);
	if (!token_len)
		token_len = ft_is_redir(line);
	if (!token_len)
		token_len = ft_isparentheses(line);
	if (!token_len)
		token_len = operator_len(line);
	return (token_len);
}

/**
 * @brief gives the redirection type
 * @param str
 * @return int on success , false on failiure
 */
int	redir_identifier(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (REDIR_APPEND);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (REDIR_HEREDOC);
	if (str[0] == '<')
		return (REDIR_IN);
	if (str[0] == '>')
		return (REDIR_OUT);
	return (0);
}

/**
 * @brief checks if the current string is an operator
 * @param str
 * @return returns the length of the operator on success and false on failure
 */
int	operator_len(char *str) //
{
	int	i;
	int	len;
	int	type;

	i = 0;
	len = ft_is_operator(&str[i]);
	if (!len)
		return (0);
	type = token_lexer(&str[i]);
	i += len;
	len = i;
	return (i);
}

/**
 * @brief Counts the number of chars excluding operators, pipes and parentheses
 * @param str
 * @return the length of a command or arg, false on failure;
 */
int	count_chars(char *str)
{
	int	i;
	int	set;

	i = 0;
	if (ft_isparentheses(str))
		return (0);
	set = ft_syntax_analyzer(&str[i]);
	if (!set)
		return (0);
	i += set;
	return (i);
}

int	skip_quoted_str(char *str, char quote)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}

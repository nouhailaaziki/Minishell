/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:09:54 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/20 17:01:17 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

int handle_quotes(char *str, char c) // Handle quote expansion during tokenization
{
	int		i;
	char	commander;
	int		in_quote;

	1 && (i = 1, in_quote = 1, commander = c);
	while (str[i] != '\0' )
	{
		if (ft_is_operator(&str[i]) && !in_quote)
			break;
		if (str[i] == commander && in_quote)
			in_quote = 0;
		else if (ft_isquote(str[i]) && !in_quote)
		{
			if (str[i] != commander)
				commander = str[i];
			in_quote = 1;
		}
		if ((str[i] == ' ' || ft_isparentheses(&str[i])) && !in_quote)
			break;
		i++;
	}
	if (in_quote)
		return (0);
	return (i);
}
/**
 * @brief check if the parenthese count is correct
 * @param str the string to check for
 * @return Retuns 1 on success , and 0 on Failure
 */
int parentheses_counter(char *str)
{
	int i;
	int parentheses;

	parentheses = 1;
	i = 1;
	while (str[i] && parentheses != 0) // TODO: look at this again
	{
		 if (str[i] == '(')
			parentheses += 1;
		else if (str[i] == ')')
			parentheses -= 1;
		i++;
	}
	if (parentheses != 0)
		return (0);
	return (i);
}
int handle_parentheses(t_token *head)
{
	t_token *current;

	current = head;
	while(current&& current->next)
	{
		if(current->type == TOKEN_PAREN_LEFT && current->next->type == TOKEN_PAREN_RIGHT)
			return (0);
		if(current )
		current = current->next;
	}
	return 1;
}
// }
// {
// 	if(ft_isparentheses(str) && parentheses_counter(str))
// 		return 1;
// 	return 0;}
	// parentheses++;
	// while(str[parentheses])
	// {
	// 	result = 0;
	// 	parentheses += skip_spaces(&str[parentheses]);
	// 	result = ft_syntax_analyzer(&str[parentheses]);
	// 	if(result)
	// 		parentheses += result;
	// 	else if(!result)
	// 	{
	// 	result = operator_len(&str[parentheses]);
	// 	parentheses += result;
	// 	}
	// 	if (!result || ft_before_x(&str[i], ft_isparentheses))
	// 		return 0;
	// }


int ft_syntax_analyzer(char *str)
{
	int i;
	int set;

	i = 0;
	while (str[i] && !ft_isparentheses(&str[i]) &&!ft_is_operator(&str[i]) && !ft_isspace(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			set = handle_quotes(&str[i], str[i]);
			if (!set)
				return (0);
			i += set;
			break;
		}
		if (ft_isparentheses(&str[i]) && str[i] == '(')
			return (0);
		i++;
	}
		// if (ft_isparentheses(&str[i]) | ft_before_x(&str[i],ft_isparentheses)) // if the word is followed directly by parentheses
		// 	return (0);
	return (i);
}

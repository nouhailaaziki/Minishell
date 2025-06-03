/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:09:54 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/03 18:06:23 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"


int handle_quotes(char *str, char c)
{
	int		i;
	char	commander;
	int		in_quote;

	1 && (i = 1, in_quote = 1, commander = c);
	while (str[i] != '\0' )// && (!ft_isparentheses(&str[i]) && !in_quote))
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
	// ft_printf("salam <%s>\n", &str[i]);
	return (i);
}

int	handle_parentheses(char *str)
{
	int	i;
	int parentheses;
	// int result;
	if (str[0] == ')' || str[1] == ')')
		return (0);
	parentheses = 1;
	i = 1;
	while (str[i] && parentheses != 0)
	{
		if (str[i] == ')')
			parentheses -= 1;
		else if (str[i] == '(')
			parentheses += 1;
		i++;
	}
	if (parentheses != 0)
		return (0);
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
	return (i);
}

int count_chars(char *str)
{
	int	i;
	int	set;

	i = 0;
	if (str[i] == '(' || str[i] == ')')
	{
		// TODO HANDLE PARENTHESES CORRECTLY
		set = handle_parentheses(&str[i]);
		if (!set)
			return (0);
		i += set;
		return i;
	}
	set = ft_syntax_analyzer(&str[i]);
	if (!set || ft_before_x(&str[i],ft_isparentheses) ) // ||(head && tokens_init(head,&str[i])))
		return (0);
	i += set;
	return (i);
}

int ft_syntax_analyzer(char *str)
{
	int i;
	int set;

	i = 0;
	while (str[i] && !ft_is_operator(&str[i]) && !ft_isspace(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			set = handle_quotes(&str[i], str[i]);
			if (!set)
				return (0);
			i += set;
			break;
		}
		if (ft_isparentheses(&str[i]))
			return (0);
		i++;
	}
		if (ft_isparentheses(&str[i]) | ft_before_x(&str[i],ft_isparentheses))
			return (0);
	return i;
}

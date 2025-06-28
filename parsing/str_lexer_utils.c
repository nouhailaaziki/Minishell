/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_lexer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:56:38 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/28 11:30:39 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

int	ft_isparentheses(char *c)
{
	if (c && (c[0] == '(' || c[0] == ')'))
		return (1);
	return (0);
}

char	ft_isquote(char c)
{
	if (c == '\'')
		return ('\'');
	else if (c == '\"')
		return ('\"');
	return (0);
}

int	ft_is_redir(char *c)
{
	if (!ft_strncmp(c, "<<", 2) || !ft_strncmp(c, ">>", 2))
		return (2);
	else if (c[0] == '>' || c[0] == '<')
		return (1);
	return (0);
}

int	ft_is_bonus_operator(char *str)
{
	if (!str)
		return (0);
	else if (!ft_strncmp(str, "||", 2) || !ft_strncmp(str, "&&", 2))
		return (1);
	return (0);
}

int	ft_is_operator(char *c)
{
	if (ft_is_bonus_operator(c))
		return (2);
	else if (*c == '|')
		return (1);
	return (0);
}

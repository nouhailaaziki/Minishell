/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:03:37 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/20 09:39:51 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	link_nodes(t_var **head, t_var *node)
{
	t_var	*tmp;

	if (!node)
	{
		ft_putendl_fd("Error Node is Empty\n", 2);
		return ;
	}
	if (!head || !*head)
	{
		*head = node;
		node->next = NULL;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->next = NULL;
}

int	is_valid_key(char key)
{
	if (!key)
		return (0);
	if (key == '?' || key == '$' || ft_isquote(key)
		|| ft_isalpha(key) || key == '_')
		return (1);
	return (0);
}

void	check_quote(char *start, char *end, int *quote)
{
	int	i;

	i = 0;
	while (start != end)
	{
		if (*start == '"' || *start == '\'')
		{
			if (*quote == 0)
				*quote = *start;
			else if (*quote == *start)
				*quote = 0;
		}
		start++;
	}
}

int	value_scan(char *arg)
{
	int		i;
	char	*value;

	i = 0;
	value = ft_strchr(arg, '=');
	if (!value || !++value)
		return (0);
	if (is_in_quotes(arg))
		return (0);
	return (1);
}

int	key_scan(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	if (ft_strchr(arg, '\'') || ft_strchr(arg, '\"'))
		return (0);
	if (!is_valid_key(arg[i]))
		return (0);
	while (arg[i])
	{
		if ((arg[i] == '+' && arg[i + 1] == '=' ) || arg[i] == '=')
			break ;
		else if (!ft_isalnum(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

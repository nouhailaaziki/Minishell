/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expand_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:47:38 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/16 11:08:02 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	inject_quotes(char **str)
{
	char	*value;
	char	*new_value;
	char	*tmp;

	value = ft_strchr(*str, '=');
	if (!value || !++value)
		return ;
	new_value = ft_calloc(sizeof(char), ft_strlen(value) + 2);
	if (!new_value)
		return ;
	tmp = new_value;
	new_value[0] = '"';
	new_value = ft_strjoin(new_value, *str);
	free(tmp);
	new_value[ft_strlen(*str) + 1] = '\"';
	free(*str);
	*str = new_value;
}

void	clean_tabs(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			i++;
		else
			str[i++] = ' ';
	}
}

void	store_args(t_token **list, char **origin)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	while (origin && origin[i])
	{
		if (multi_str_included(origin[i]))
		{
			tmp = ft_split_args(origin[i]);
			j = 0;
			while (tmp && tmp[j])
			{
				clean_tabs(tmp[i]);
				link_token(list, new_token(tmp[j++], 1));
			}
			free_cmd(tmp);
		}
		else
			link_token(list, new_token(origin[i], 1));
		i++;
	}
}

void	filter_empty_nodes(t_token **head, size_t *argc)
{
	t_token	*current;
	t_token	*next;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		if (current->value && current->value[0] == '\0')
		{
			if (current->prev)
				current->prev->next = current->next;
			else
				*head = current->next;
			free(current->value);
			free(current);
		}
		else
			(*argc)++;
		current = next;
	}
}

char	**rebuild_cmd(t_token **list, size_t argc)
{
	char	**new_array;
	t_token	*current;
	int		i;

	if (!argc)
		return (NULL);
	current = *list;
	new_array = ft_calloc(argc + 1, sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (current)
	{
		new_array[i++] = ft_strdup(current->value);
		current = current->next;
	}
	new_array[i] = (NULL);
	return (new_array);
}

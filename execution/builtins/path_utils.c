/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:10:55 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/04 09:11:55 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	count_leading_dotdots(const char *path)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (path[i])
	{
		if (path[i] == '.' && path[i + 1] == '.'
			&& (path[i + 2] == '/' || path[i + 2] == '\0'))
		{
			count++;
			i += 2;
			if (path[i] == '/')
				i++;
		}
		else
			break ;
	}
	return (count);
}

char	*get_next_component(const char *path, int *start, int *end)
{
	int	i;

	i = *start;
	while (path[i] == '/')
		i++;
	*start = i;
	while (path[i] && path[i] != '/')
		i++;
	*end = i;
	if (*start == *end)
		return (NULL);
	return (na_substr(path, *start, *end - *start));
}

char	*handle_dotdots(char *new_path, int dotdots)
{
	char	*temp;

	while (dotdots-- > 0)
	{
		temp = ft_strrchr(new_path, '/');
		if (!temp)
			return (NULL);
		*temp = '\0';
		if (temp == new_path)
			break ;
	}
	return (new_path);
}

char	*handle_component(char *new_path, const char *component)
{
	char	*temp;
	char	*temp2;

	if (component && *component)
	{
		temp = na_strjoin(new_path, "/");
		if (!temp)
			return (NULL);
		temp2 = na_strjoin(temp, component);
		new_path = temp2;
		if (!new_path)
			return (NULL);
	}
	return (new_path);
}

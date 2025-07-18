/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:01:02 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/16 11:38:43 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	resize_matches_if_needed(t_match_data *data)
{
	char	**new_matches;
	size_t	i;

	if (data->count < data->capacity)
		return ;
	data->capacity *= 2;
	new_matches = malloc(data->capacity * sizeof(char *));
	if (!new_matches)
	{
		perror("malloc");
		free(data->matches);
		data->matches = NULL;
		return ;
	}
	i = 0;
	while (i < data->count)
	{
		new_matches[i] = data->matches[i];
		i++;
	}
	free(data->matches);
	data->matches = new_matches;
}

void	sort_matches(char **matches, size_t count)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (strcmp(matches[j], matches[j + 1]) > 0)
			{
				temp = matches[j];
				matches[j] = matches[j + 1];
				matches[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

size_t	match_pattern(const char *pattern, const char *string)
{
	while (*pattern)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (*pattern == '\0')
				return (1);
			while (*string)
			{
				if (match_pattern(pattern, string))
					return (1);
				string++;
			}
			return (0);
		}
		else if (*pattern == *string)
		{
			pattern++;
			string++;
		}
		else
			return (0);
	}
	return (*string == '\0');
}

void	cleanup_string_array(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

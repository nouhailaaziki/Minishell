/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_matcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:11:15 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/20 13:17:03 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

char	**find_matching_entries(const char *pattern, const char *pwd,
size_t *matches_count)
{
	DIR				*dir;
	t_match_data	data;

	data.capacity = 10;
	data.matches = malloc(data.capacity * sizeof(char *));
	if (!data.matches)
		return (NULL);
	data.count = 0;
	dir = opendir(pwd);
	if (!dir)
	{
		perror("opendir");
		free(data.matches);
		return (NULL);
	}
	process_directory_entries(dir, pattern, &data);
	closedir(dir);
	*matches_count = data.count;
	return (data.matches);
}

void	process_directory_entries(DIR *dir, const char *pattern,
t_match_data *data)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if (match_pattern(pattern, entry->d_name))
		{
			resize_matches_if_needed(data);
			if (!data->matches)
				break ;
			data->matches[(data->count)++] = ft_strdup(entry->d_name);
		}
		entry = readdir(dir);
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

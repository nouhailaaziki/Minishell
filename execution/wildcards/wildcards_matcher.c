/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_matcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:41:53 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/22 20:43:37 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

char	**prepare_and_find_matches(const char *pattern, const char *pwd,
size_t *matches_count)
{
	char	*optimized_pattern;
	char	*masked_pattern;
	char	**matches;

	optimized_pattern = collapse_consecutive_asterisks(pattern);
	if (!optimized_pattern)
		return (perror("malloc"), NULL);
	masked_pattern = create_masked_pattern(optimized_pattern);
	free(optimized_pattern);
	if (!masked_pattern)
		return (perror("malloc"), NULL);
	matches = find_matching_entries(masked_pattern, pwd, matches_count);
	free(masked_pattern);
	return (matches);
}

char	*collapse_consecutive_asterisks(const char *pattern)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*new_pattern;

	if (!pattern)
		return (NULL);
	len = strlen(pattern);
	new_pattern = (char *)malloc(len + 1);
	if (!new_pattern)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		new_pattern[j++] = pattern[i];
		if (pattern[i] == '*')
			while (i + 1 < len && pattern[i + 1] == '*')
				i++;
		i++;
	}
	new_pattern[j] = '\0';
	return (new_pattern);
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_finder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:08:39 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/20 09:15:52 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

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
			if (ft_strcmp(matches[j], matches[j + 1]) > 0)
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
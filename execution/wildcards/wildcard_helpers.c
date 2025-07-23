/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:13:02 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/20 13:30:44 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

char	**build_new_argv(char **old_argv, char **matches, size_t arg_index,
size_t matches_count)
{
	char	**new_argv;
	size_t	new_argc;
	size_t	current_pos;
	size_t	i;
	size_t	old_argc;

	old_argc = 0;
	while (old_argv[old_argc])
		old_argc++;
	new_argc = old_argc - 1 + matches_count;
	new_argv = malloc((new_argc + 1) * sizeof(char *));
	if (!new_argv)
		return (NULL);
	current_pos = 0;
	i = 0;
	while (i < arg_index)
		new_argv[current_pos++] = ft_strdup(old_argv[i++]);
	i = 0;
	while (i < matches_count)
		new_argv[current_pos++] = ft_strdup(matches[i++]);
	i = arg_index + 1;
	while (old_argv[i])
		new_argv[current_pos++] = ft_strdup(old_argv[i++]);
	new_argv[current_pos] = NULL;
	return (new_argv);
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

void	cleanup_matches(char **matches, size_t matches_count)
{
	size_t	i;

	i = 0;
	while (i < matches_count)
		free(matches[i++]);
	free(matches);
}

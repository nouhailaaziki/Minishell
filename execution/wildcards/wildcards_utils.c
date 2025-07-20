/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:01:02 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/20 09:15:24 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

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

char    **build_new_argv(char **old_argv, char **matches, size_t arg_index,
size_t matches_count)
{
    char    **new_argv;
    size_t  new_argc;
    size_t  current_pos;
    size_t  i;
    size_t  old_argc = 0;

    while(old_argv[old_argc])
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

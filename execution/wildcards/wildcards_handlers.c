/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:44:02 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/23 20:21:38 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

size_t	handle_matches_found(char ***cmd, char **matches,
size_t matches_count, size_t arg_index)
{
	char	**new_argv;

	sort_matches(matches, matches_count);
	new_argv = build_new_argv(*cmd, matches, arg_index, matches_count);
	cleanup_matches(matches, matches_count);
	if (!new_argv)
	{
		perror("malloc");
		return (arg_index + 1);
	}
	cleanup_string_array(*cmd);
	*cmd = new_argv;
	return (matches_count);
}

size_t	handle_no_matches(char ***cmd, char **matches,
const char *pattern, size_t arg_index)
{
	char	**new_argv;
	char	*temp_match[2];

	free(matches);
	temp_match[0] = (char *)pattern;
	temp_match[1] = NULL;
	new_argv = build_new_argv(*cmd, temp_match, arg_index, 1);
	if (!new_argv)
	{
		perror("malloc");
		return (arg_index + 1);
	}
	cleanup_string_array(*cmd);
	*cmd = new_argv;
	return (1);
}

size_t	handle_wildcards(char ***cmd, const char *pattern,
size_t arg_index, const char *pwd)
{
	char	**matches;
	size_t	matches_count;

	matches = find_matching_entries(pattern, pwd, &matches_count);
	if (!matches)
	{
		perror("malloc");
		return (arg_index + 1);
	}
	if (matches_count > 0)
		return (handle_matches_found(cmd, matches,
				matches_count, arg_index));
	else
		return (handle_no_matches(cmd, matches, pattern, arg_index));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:10:16 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/22 15:32:33 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

size_t	process_quoted_wildcard(t_tree *cmd_node, size_t i)
{
	char	*pattern_no_quotes;

	pattern_no_quotes = remove_quotes(cmd_node->cmd[i]);
	if (!pattern_no_quotes)
	{
		perror("malloc");
		return (0);
	}
	free(cmd_node->cmd[i]);
	cmd_node->cmd[i] = pattern_no_quotes;
	return (1);
}

char	*create_masked_pattern(const char *s)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	bool	in_single_quotes;
	bool	in_double_quotes;

	i = 0;
	j = 0;
	in_single_quotes = false;
	in_double_quotes = false;
	new_str = malloc(strlen(s) + 1);
	if (!new_str)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (s[i] == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else
		{
			if (s[i] == '*' && (in_single_quotes || in_double_quotes))
				new_str[j++] = 1;
			else
				new_str[j++] = s[i];
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

size_t	process_unquoted_wildcard(t_tree *cmd_node, size_t i, char *pwd)
{
	char	*masked_pattern;
	char	**matches;
	size_t	matches_count;
	size_t	expansion_count;
	char	*literal_arg;
	char	*temp_match[2];
	char	**new_argv;

	masked_pattern = create_masked_pattern(cmd_node->cmd[i]);
	if (!masked_pattern)
		return (perror("malloc"), 0);
	matches = find_matching_entries(masked_pattern, pwd, &matches_count);
	free(masked_pattern);
	if (!matches)
		return (perror("malloc"), 0);
	if (matches_count > 0)
		expansion_count = handle_matches_found(cmd_node,
				matches, matches_count, i);
	else
	{
		free(matches);
		literal_arg = remove_quotes(cmd_node->cmd[i]);
		if (!literal_arg)
			return (perror("malloc"), 0);
		7889 && (temp_match[0] = literal_arg, temp_match[1] = NULL);
		new_argv = build_new_argv(cmd_node->cmd, temp_match, i, 1);
		if (!new_argv)
		{
			(perror("malloc"), free(literal_arg));
			return (0);
		}
		cleanup_string_array(cmd_node->cmd);
		cmd_node->cmd = new_argv;
		expansion_count = 1;
		free(literal_arg);
	}
	return (expansion_count);
}

size_t	process_no_wildcard(t_tree *cmd_node, size_t i)
{
	char	*pattern_no_quotes;

	pattern_no_quotes = remove_quotes(cmd_node->cmd[i]);
	if (!pattern_no_quotes)
	{
		perror("malloc");
		return (0);
	}
	free(cmd_node->cmd[i]);
	cmd_node->cmd[i] = pattern_no_quotes;
	return (1);
}

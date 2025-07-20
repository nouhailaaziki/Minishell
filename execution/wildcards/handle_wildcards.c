/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 11:56:28 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/20 12:02:13 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

bool	has_quoted_wildcard(const char *s)
{
	bool	in_single_quotes;
	bool	in_double_quotes;

	in_single_quotes = false;
	in_double_quotes = false;
	while (*s)
	{
		if (*s == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (*s == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (*s == '*' && (in_single_quotes || in_double_quotes))
			return (true);
		s++;
	}
	return (false);
}

bool	has_unquoted_wildcard(const char *s)
{
	bool	in_single_quotes;
	bool	in_double_quotes;

	in_single_quotes = false;
	in_double_quotes = false;
	while (*s)
	{
		if (*s == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (*s == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (*s == '*' && !in_single_quotes && !in_double_quotes)
			return (true);
		s++;
	}
	return (false);
}

char	*remove_quotes(const char *s)
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
			new_str[j++] = s[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

size_t	handle_wildcards(t_tree *cmd_node, const char *pattern,
size_t arg_index, const char *pwd)
{
	char	**matches;
	size_t	matches_count;
	char	**new_argv;
	char	*temp_match[2];
	size_t	i;

	matches = find_matching_entries(pattern, pwd, &matches_count);
	if (!matches)
	{
		perror("malloc");
		return (arg_index + 1);
	}
	if (matches_count > 0)
	{
		sort_matches(matches, matches_count);
		new_argv = build_new_argv(cmd_node->cmd, matches, arg_index,
				matches_count);
		i = 0;
		while (i < matches_count)
			free(matches[i++]);
		free(matches);
		if (!new_argv)
		{
			perror("malloc");
			return (arg_index + 1);
		}
		cleanup_string_array(cmd_node->cmd);
		cmd_node->cmd = new_argv;
		return (matches_count);
	}
	else
	{
		free(matches);
		temp_match[0] = (char *)pattern;
		temp_match[1] = NULL;
		new_argv = build_new_argv(cmd_node->cmd, temp_match, arg_index, 1);
		if (!new_argv)
		{
			perror("malloc");
			return (arg_index + 1);
		}
		cleanup_string_array(cmd_node->cmd);
		cmd_node->cmd = new_argv;
		return (1);
	}
}

void	check_for_wildcards(t_tree *cmd_node, t_stash *stash)
{
	size_t	i;
	char	*pwd;
	char	*pattern_no_quotes;
	size_t	expansion_count;

	if (!cmd_node || !cmd_node->cmd)
		return ;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup(stash->pwd_backup);
	if (!pwd)
		return (perror("malloc"));
	i = 0;
	while (cmd_node->cmd[i])
	{
		if (has_quoted_wildcard(cmd_node->cmd[i]))
		{
			pattern_no_quotes = remove_quotes(cmd_node->cmd[i]);
			if (!pattern_no_quotes)
			{
				perror("malloc");
				break ;
			}
			free(cmd_node->cmd[i]);
			cmd_node->cmd[i] = pattern_no_quotes;
			i++;
		}
		else if (has_unquoted_wildcard(cmd_node->cmd[i]))
		{
			pattern_no_quotes = remove_quotes(cmd_node->cmd[i]);
			if (!pattern_no_quotes)
			{
				perror("malloc");
				break ;
			}
			expansion_count = handle_wildcards(cmd_node,
					pattern_no_quotes, i, pwd);
			free(pattern_no_quotes);
			i += expansion_count;
		}
		else
		{
			pattern_no_quotes = remove_quotes(cmd_node->cmd[i]);
			if (!pattern_no_quotes)
			{
				perror("malloc");
				break ;
			}
			free(cmd_node->cmd[i]);
			cmd_node->cmd[i] = pattern_no_quotes;
			i++;
		}
	}
	free(pwd);
}

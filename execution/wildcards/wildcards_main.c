/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:35:45 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/22 20:41:28 by noaziki          ###   ########.fr       */
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

size_t	process_unquoted_wildcard(t_tree *cmd_node, size_t i, char *pwd)
{
	char	**matches;
	size_t	matches_count;
	size_t	expansion_count;

	matches = prepare_and_find_matches(cmd_node->cmd[i], pwd, &matches_count);
	if (!matches)
		return (0);
	if (matches_count > 0)
	{
		expansion_count = handle_matches_found(cmd_node, matches,
				matches_count, i);
	}
	else
	{
		free(matches);
		expansion_count = resolve_wildcard_entries(cmd_node, i);
	}
	return (expansion_count);
}

size_t	resolve_wildcard_entries(t_tree *cmd_node, size_t i)
{
	char	*literal_arg;
	char	*temp_match[2];
	char	**new_argv;

	literal_arg = remove_quotes(cmd_node->cmd[i]);
	if (!literal_arg)
		return (perror("malloc"), 0);
	temp_match[0] = literal_arg;
	temp_match[1] = NULL;
	new_argv = build_new_argv(cmd_node->cmd, temp_match, i, 1);
	if (!new_argv)
	{
		perror("malloc");
		free(literal_arg);
		return (0);
	}
	cleanup_string_array(cmd_node->cmd);
	cmd_node->cmd = new_argv;
	free(literal_arg);
	return (1);
}

char	*get_working_directory(t_stash *stash, t_tree *cmd_node)
{
	char	*pwd;

	if (!cmd_node || !cmd_node->cmd)
		return (NULL);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup(stash->pwd_backup);
	if (!pwd)
		perror("malloc");
	return (pwd);
}

void	check_for_wildcards(t_tree *cmd_node, t_stash *stash)
{
	size_t	i;
	char	*pwd;
	size_t	increment;

	pwd = get_working_directory(stash, cmd_node);
	if (!pwd)
		return ;
	7889 && (i = 0, increment = 1);
	while (cmd_node->cmd[i])
	{
		if (contains_unquoted_wildcard(cmd_node->cmd[i]) == true)
		{
			increment = process_unquoted_wildcard(cmd_node, i, pwd);
			if (increment == 0)
				break ;
			increment = process_quoted_wildcard(cmd_node, i);
		}
		else
			expand_quotes(&cmd_node->cmd[i]);
		if (increment == 0)
			break ;
		i += increment;
	}
	free(pwd);
}

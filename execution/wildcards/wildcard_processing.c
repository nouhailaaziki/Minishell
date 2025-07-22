/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:10:16 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/22 10:54:11 by noaziki          ###   ########.fr       */
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
	char	*pattern_no_quotes;
	size_t	expansion_count;

	pattern_no_quotes = remove_quotes(cmd_node->cmd[i]);
	if (!pattern_no_quotes)
	{
		perror("malloc");
		return (0);
	}
	expansion_count = handle_wildcards(cmd_node, pattern_no_quotes, i, pwd);
	free(pattern_no_quotes);
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

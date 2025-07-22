/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:12:20 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/22 17:56:22 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

bool	contains_unquoted_wildcard(const char *s)
{
	bool	in_single;
	bool	in_double;

	in_single = false;
	in_double = false;
	while (*s)
	{
		if (*s == '\'' && !in_double)
			in_single = !in_single;
		else if (*s == '"' && !in_single)
			in_double = !in_double;
		else if (*s == '*' && !in_single && !in_double)
			return (true);
		s++;
	}
	return (false);
}

void	check_for_wildcards(t_tree *cmd_node, t_stash *stash)
{
	size_t	i;
	char	*pwd;
	size_t	increment;

	if (!cmd_node || !cmd_node->cmd)
		return ;
	pwd = get_working_directory(stash);
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

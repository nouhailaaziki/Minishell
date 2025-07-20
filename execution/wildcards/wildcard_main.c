/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:12:20 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/20 13:12:56 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

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
	i = 0;
	while (cmd_node->cmd[i])
	{
		if (has_quoted_wildcard(cmd_node->cmd[i]))
			increment = process_quoted_wildcard(cmd_node, i);
		else if (has_unquoted_wildcard(cmd_node->cmd[i]))
			increment = process_unquoted_wildcard(cmd_node, i, pwd);
		else
			increment = process_no_wildcard(cmd_node, i);
		if (increment == 0)
			break ;
		i += increment;
	}
	free(pwd);
}

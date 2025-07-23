/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:12:20 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/22 09:31:00 by yrhandou         ###   ########.fr       */
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
	increment = 1;
	while (cmd_node->cmd[i])
	{
		if (has_quoted_wildcard(cmd_node->cmd[i]))
			increment = process_quoted_wildcard(cmd_node, i);
		else if (has_unquoted_wildcard(cmd_node->cmd[i]))
			increment = process_unquoted_wildcard(cmd_node, i, pwd);
		else
			expand_quotes(&cmd_node->cmd[i]);
		if (increment == 0)
			break ;
		i += increment;
	}
	free(pwd);
}

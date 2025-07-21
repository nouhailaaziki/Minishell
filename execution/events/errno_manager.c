/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 05:31:43 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/21 13:52:07 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	is_it_dir(char *cmd)
{
	struct stat	path_stat;

	if (!access(cmd, F_OK) && !stat(cmd, &path_stat)
		&& S_ISDIR(path_stat.st_mode))
	{
		(ft_putstr_fd("L33tShell: ", 2), ft_putstr_fd(cmd, 2));
		ft_putendl_fd(": is a directory", 2);
		exit(126);
	}
}

void	errno_manager(char	*cmd)
{
	char	*error;

	error = na_strjoin("L33tShell: ", cmd);
	perror(error);
	if (errno == 13 || errno == 20)
		exit(126);
	else if (errno == 2)
		exit(127);
}

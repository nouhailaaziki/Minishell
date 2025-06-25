/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puterror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:19:41 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/23 17:57:55 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

// exemple : "L33tShell: cd: file_x: No such file or directory\n"
int	puterror(int program, char *cmd, char *arg, char *error)
{
	char	*message;

	if (program)
	{
		message = na_strjoin("L33tShell: ", cmd);
		message = na_strjoin(message, arg);
		message = na_strjoin(message, error);
	}
	else
	{
		message = na_strjoin(cmd, arg);
		message = na_strjoin(message, error);
	}
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

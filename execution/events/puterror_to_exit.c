/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puterror_to_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:23:06 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/09 08:07:22 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	puterror_to_exit(char *cmd, char *error, int ex)
{
	char	*message;

	message = na_strjoin("LeetShell: ", cmd);
	message = na_strjoin(message, error);
	write(1, message, ft_strlen(message));
	free_all_tracked();
	exit (ex);
}

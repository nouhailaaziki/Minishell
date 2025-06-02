/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puterror_to_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:23:06 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/01 15:10:51 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

void	puterror_to_exit(char *cmd, char *error, int ex)
{
	char	*message;

	message = na_strjoin("LeetShell: ", cmd);
	message = na_strjoin(message, error);
	write(1, message, ft_strlen(message));
	free_all_tracked();
	exit (ex);
}

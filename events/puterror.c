/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puterror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:19:41 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/03 16:42:31 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

int	puterror(char *cmd, char *error)
{
	char	*message;

	message = na_strjoin("LeetShell: ", cmd);
	message = na_strjoin(message, error);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
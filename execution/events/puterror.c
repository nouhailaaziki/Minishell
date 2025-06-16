/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puterror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:19:41 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/09 08:07:22 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	puterror(char *cmd, char *error)
{
	char	*message;

	message = na_strjoin("LeetShell: ", cmd);
	message = na_strjoin(message, error);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

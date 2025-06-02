/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isallchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:12:01 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/02 12:44:25 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

int	ft_isallchar(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

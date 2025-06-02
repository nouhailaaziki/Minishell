/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 09:39:06 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/01 12:24:41 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*h;

	i = 0;
	h = (unsigned char *) b;
	while (i < len)
	{
		h[i] = (unsigned char) c;
		i++;
	}
	return (b);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 09:39:06 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/28 09:52:00 by yrhandou         ###   ########.fr       */
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

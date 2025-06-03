/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:04:07 by yrhandou          #+#    #+#             */
/*   Updated: 2024/11/22 18:28:24 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*dest;
	const unsigned char	*srce;

	dest = (unsigned char *)dst;
	srce = (const unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (dest > srce)
	{
		while (len--)
			dest[len] = srce[len];
	}
	else if (dest < srce)
	{
		i = 0;
		while (i < len)
		{
			dest[i] = srce[i];
			i++;
		}
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:05:42 by yrhandou          #+#    #+#             */
/*   Updated: 2025/05/18 09:17:59 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dest;
	const unsigned char	*sorc;

	dest = (unsigned char *)dst;
	sorc = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dest[i] = sorc[i];
		i++;
	}
	return (dst);
}

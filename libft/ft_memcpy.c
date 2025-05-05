/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <contact.naziki@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:19:40 by noaziki           #+#    #+#             */
/*   Updated: 2024/11/15 14:12:44 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*str;
	unsigned char		*dest;

	i = 0;
	str = (const unsigned char *) src;
	dest = (unsigned char *) dst;
	if (dst == src)
		return (dst);
	while (i < n)
	{
		dest[i] = str[i];
		i++;
	}
	return (dst);
}

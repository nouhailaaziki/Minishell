/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <contact.naziki@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:42:27 by noaziki           #+#    #+#             */
/*   Updated: 2024/11/17 14:29:20 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	l;
	size_t	ld;
	size_t	ls;

	if ((!dest && size == 0) || size == 0)
		return (ft_strlen(src));
	l = 0;
	ld = 0;
	ls = ft_strlen(src);
	while (dest[ld] && ld < size)
		ld++;
	if (ld == size)
		return (size + ls);
	if (ld < size - 1)
	{
		while (src[l] && ld + l < size - 1)
		{
			dest[ld + l] = src[l];
			l++;
		}
	}
	dest[ld + l] = '\0';
	return (ld + ls);
}

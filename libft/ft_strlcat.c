/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:08:00 by yrhandou          #+#    #+#             */
/*   Updated: 2024/11/21 19:45:41 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	ld;
	size_t	ls;
	size_t	j;

	ld = ft_strlen(dst);
	ls = ft_strlen(src);
	j = 0;
	if (dstsize == 0)
		return (ls);
	if (dstsize <= ld)
		return (dstsize + ls);
	while (src[j] != '\0' && j + ld < dstsize -1)
	{
		dst[ld + j] = src[j];
		j++;
	}
	dst[ld + j] = '\0';
	return (ld + ls);
}

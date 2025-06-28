/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   na_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:11:06 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/28 09:52:00 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

void	*na_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	total_bytes;

	total_bytes = count * size;
	if (count && total_bytes / count != size)
		return (NULL);
	p = nalloc(count * size);
	if (!p)
		return (NULL);
	ft_memset(p, 0, count * size);
	return (p);
}

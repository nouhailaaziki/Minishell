/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   na_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:11:06 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/01 12:25:37 by noaziki          ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   na_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:47:50 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/29 08:59:53 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

char	*na_strdup(const char *s)
{
	int		i;
	char	*p;

	if (!s)
		return (NULL);
	i = 0;
	p = (char *)nalloc(ft_strlen(s) + 1);
	if (!p)
		return (NULL);
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

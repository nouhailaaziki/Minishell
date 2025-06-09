/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   na_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:47:50 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/09 08:07:22 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

char	*na_strdup(const char *s)
{
	int		i;
	char	*p;

	i = 0;
	p = (char *)nalloc(ft_strlen(s) + 1);
	if (!p)
		return (NULL);
	while (s && s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

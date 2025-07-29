/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   na_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:51:37 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/29 09:00:09 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

char	*na_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	a;
	size_t	lens;
	char	*p;

	a = start + len;
	i = 0;
	if (s == NULL)
		return (NULL);
	lens = ft_strlen(s);
	if (start >= lens)
		return (na_strdup(""));
	if (len > lens - start)
		len = lens - start;
	p = (char *)nalloc(len + 1);
	if (p == NULL)
		return (NULL);
	while (start < a && s[start])
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}

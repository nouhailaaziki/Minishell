/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:46:35 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/28 09:30:54 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

char	*ft_strdup(const char *s1)
{
	size_t			i;
	size_t			len;
	char			*str;

	len = ft_strlen(s1);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

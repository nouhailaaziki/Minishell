/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:06:25 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/02 22:52:05 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	length;
	char	*str;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	if (length <= start)
		len = 0;
	else if (len > length - start)
		len = length - start;
	str = ft_calloc( len + 1,sizeof(char) );
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		str[i++] = s[start++];
	}
	str[i] = '\0';
	return (str);
}

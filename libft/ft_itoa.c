/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 08:46:40 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/16 10:35:57 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

 int	count_num(int num)
{
	int	count;

	count = 1;
	while (num / 10 != 0)
	{
		count++;
		num = num / 10;
	}
	return (count);
}

 char	*itoa_ft(int count, int n)
{
	char	*str;

	str = (char *)malloc(count + 2);
	if (!str)
		return (NULL);
	str[count + 1] = '\0';
	str[0] = '-';
	while (count)
	{
		str[count--] = (n % 10) * (-1) + '0';
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*str;

	count = count_num(n);
	if (n < 0)
		return (itoa_ft(count, n));
	str = (char *)malloc(count + 1);
	if (!str)
		return (NULL);
	else
		str[count] = '\0';
	while (count--)
	{
		str[count] = n % 10 + '0';
		n = n / 10;
	}
	return (str);
}

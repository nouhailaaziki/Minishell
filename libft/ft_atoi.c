/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:33:26 by yrhandou          #+#    #+#             */
/*   Updated: 2025/05/18 19:43:12 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	sign_check(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign *= -1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	long			temp;
	long			result;

	sign = 1;
	i = 0;
	result = 0;
	i = sign_check(str, &sign);
	while (ft_isdigit(str[i]))
	{
		temp = result;
		result = result * 10 + (str[i] - '0');
		if (result / 10 != temp)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		i++;
	}
	return ((int)(result * sign));
}

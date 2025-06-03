/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_modified.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 09:28:42 by yrhandou          #+#    #+#             */
/*   Updated: 2025/05/18 09:31:58 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	sign_checker(const char *str, long *sign)
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

long	ft_atoi_modified(const char *str)
{
	int		i;
	long	sign;
	long	result;

	sign = 1;
	i = 0;
	result = 0;
	i = sign_checker(str, &sign);
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		if (i > 11 && result > INT_MAX)
			return (2147483648);
		i++;
	}
	return (result * sign);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:50:32 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/28 09:52:00 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

int	skip(const char *str, int *s)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*s *= -1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			s;
	long long	w;
	long long	r;

	s = 1;
	w = 0;
	r = 0;
	i = skip(str, &s);
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + str[i] - 48;
		if (r / 10 != w)
		{
			if (s == 1)
				return (-1);
			return (0);
		}
		w = r;
		i++;
	}
	return ((int)(r * s));
}

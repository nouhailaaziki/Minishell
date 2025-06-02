/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strict_atoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:46:47 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/01 15:12:53 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

long	skip(const char *str, long *s)
{
	long	i;

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

long	strict_atoi(const char *str)
{
	long	i;
	long	s;
	long	r;

	s = 1;
	r = 0;
	i = skip(str, &s);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((r == 922337203685477580 && ((i >= 18 && s == 1 && str[i] > '7')
				|| (i >= 19 && s == -1 && str[i] > '8')))
			|| r > 922337203685477580)
			puterror_to_exit("exit", ": numeric argument required\n", 255);
		else
			r = r * 10 + str[i] - 48;
		i++;
	}
	return (r * s);
}

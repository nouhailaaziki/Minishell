/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strict_atoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:46:47 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/29 12:14:04 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

long	do_skip(const char *str, long *s)
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
	i = do_skip(str, &s);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((r == 922337203685477580 && ((i >= 18 && s == 1 && str[i] > '7')
					|| (i >= 19 && s == -1 && str[i] > '8')))
			|| r > 922337203685477580)
		{
			puterror(0, "exit", NULL, ": numeric argument required\n");
			exit(255);
		}
		else
			r = r * 10 + str[i] - 48;
		i++;
	}
	return (r * s);
}

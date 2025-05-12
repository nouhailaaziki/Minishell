/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:46:47 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/12 16:14:24 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/launchpad.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	guard_limits(long long i, long long s, long long r, char *str)
{
	if ((r == 922337203685477580 && ((i >= 18 && s == 1 && str[i] > '7')
				|| (i >= 19 && s == -1 && str[i] > '8')))
		|| r > 922337203685477580)
	{
		ft_putstr_fd("minishell: exit: ", 1);
		ft_putstr_fd(str, 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		return (1);
	}
	return (0);
}

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

long	parse_number_or_exit(const char *str, t_env **env_list)
{
	long	i;
	long	s;
	long	r;

	s = 1;
	r = 0;
	i = skip(str, &s);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (!guard_limits(i, s, r, (char *)str))
			r = r * 10 + str[i] - 48;
		else
		{
			free_env_list(env_list);
			exit (255);
		}
		i++;
	}
	return (r * s);
}

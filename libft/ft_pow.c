/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 08:31:34 by yrhandou          #+#    #+#             */
/*   Updated: 2025/05/18 08:31:45 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_pow(double num, double power)
{
	if (!num)
		return (0);
	if (!power)
		return (1);
	if (power < 0)
	{
		num = (float)(1 / num);
		power = ft_abs(power);
	}
	while (power > 1)
	{
		num *= num;
		power--;
	}
	return (num);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:10:28 by yrhandou          #+#    #+#             */
/*   Updated: 2025/05/19 12:48:30 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printnbr(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		return (ft_printstr("-2147483648"));
	}
	else if (n < 0)
	{
		n *= -1;
		count += ft_printchar('-');
		count += ft_printnbr(n);
	}
	else if (n > 9)
	{
		count += ft_printnbr(n / 10);
		count += ft_printnbr(n % 10);
	}
	else
		count += ft_printchar(n + 48);
	return (count);
}

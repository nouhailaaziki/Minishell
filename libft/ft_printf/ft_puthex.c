/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:29:50 by yrhandou          #+#    #+#             */
/*   Updated: 2025/05/19 12:53:31 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(unsigned long nbr, char flag)
{
	int		count;
	char	*hex_list;

	count = 0;
	if (flag == 'X')
		hex_list = "0123456789ABCDEF";
	else if (flag == 'x')
		hex_list = "0123456789abcdef";
	if (nbr > 15)
	{
		count += ft_puthex(nbr / 16, flag);
		count += ft_puthex(nbr % 16, flag);
	}
	else
		count += ft_printchar(hex_list[nbr]);
	return (count);
}

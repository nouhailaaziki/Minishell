/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 10:08:57 by yrhandou          #+#    #+#             */
/*   Updated: 2024/12/07 10:08:57 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_format(va_list va, char str)
{
	int	counter;

	counter = 0;
	if (str == 's')
		counter += ft_printstr(va_arg(va, char *));
	else if (str == 'c')
		counter += ft_printchar(va_arg(va, int));
	else if (str == 'p')
		counter += ft_putptr(va_arg(va, void *), 'x');
	else if (str == 'd' || str == 'i')
		counter += ft_printnbr(va_arg(va, int));
	else if (str == 'u')
		counter += ft_putuint(va_arg(va, unsigned int));
	else if (str == 'x' || str == 'X')
		counter += ft_puthex(va_arg(va, unsigned int), str);
	else
		counter += ft_printchar(str);
	return (counter);
}

int	ft_printf(const char *str, ...)
{
	int		counter;
	int		i;
	va_list	va;

	i = 0;
	counter = 0;
	va_start(va, str);
	if (write(1, "", 0) == -1)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] != '%')
			counter += ft_printchar(str[i]);
		if (str[i] == '%' && str[i + 1] != '\0')
			counter += check_format(va, str[++i]);
		i++;
	}
	va_end(va);
	return (counter);
}

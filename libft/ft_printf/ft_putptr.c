/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 11:12:44 by yrhandou          #+#    #+#             */
/*   Updated: 2025/05/19 12:48:44 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(void *ptr, char flag)
{
	int	count;

	count = 0;
	count += ft_printstr("0x");
	count += ft_puthex((unsigned long)ptr, flag);
	return (count);
}

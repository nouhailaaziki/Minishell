/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:11:30 by yrhandou          #+#    #+#             */
/*   Updated: 2025/05/19 12:54:06 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_puthex(unsigned long nbr, char flag);
int	ft_putptr(void *ptr, char flag);
int	ft_printf(const char *str, ...);
int	ft_putuint(unsigned int n);
int	ft_printstr(char *str);
int	ft_printchar(char c);
int	ft_printnbr(int n);

#endif

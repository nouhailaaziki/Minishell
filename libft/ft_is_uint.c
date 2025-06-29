/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_uint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 08:35:35 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/29 12:13:03 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

int	ft_is_uint(char *str)
{
	if (!ft_is_int(str) || str[0] == '-')
		return (0);
	if (ft_atoi(str) < 0 || (unsigned int)ft_atoi(str) > __UINT32_MAX__)
		return (0);
	return (1);
}

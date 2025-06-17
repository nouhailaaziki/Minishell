/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_sorted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 08:53:51 by yrhandou          #+#    #+#             */
/*   Updated: 2025/05/18 08:54:11 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_sorted(char **str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		if (ft_atoi_modified(str[i]) > ft_atoi_modified(str[i + 1]))
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

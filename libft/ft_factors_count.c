/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_factors_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 08:29:54 by yrhandou          #+#    #+#             */
/*   Updated: 2025/05/18 08:30:06 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_factors_count(int num)
{
	int	i;
	int	counter;
	int	*factors;

	i = 1;
	counter = 0;
	while (i <= num / 2)
	{
		if (num % i == 0)
			counter++;
		i++;
	}
	factors = ft_calloc(counter + 1, sizeof(int));
	if (!factors)
		return (NULL);
	counter = 0;
	factors[counter++] = num;
	while (i >= 1)
	{
		if (num % i == 0)
			factors[counter++] = i;
		i--;
	}
	return (factors);
}

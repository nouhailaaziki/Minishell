/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_duplicated.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 08:53:10 by yrhandou          #+#    #+#             */
/*   Updated: 2025/05/18 08:53:25 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_duplicated(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (ft_putendl_fd(RED "Failure: Empty Array", 2), FAIL);
	while (str[i])
	{
		j = i + 1;
		while (str[j])
		{
			if (ft_atoi(str[i]) == ft_atoi(str[j]))
				return (SUCCESS);
			j++;
		}
		i++;
	}
	return (FAIL);
}

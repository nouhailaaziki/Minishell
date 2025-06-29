/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 08:34:58 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/29 12:13:03 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

int	ft_is_int(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putendl_fd(RED "Failure: Empty Array", 2), FAIL);
	if ((str[0] == '-' || str[0] == '+') && str[i + 1] != '\0')
		i++;
	else if ((str[0] == '-' || str[0] == '+') && str[i + 1] == '\0')
		return (FAIL);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FAIL);
		i++;
	}
	if ((ft_atoi_modified(str) > INT_MAX || ft_atoi_modified(str) < INT_MIN))
		return (FAIL);
	return (SUCCESS);
}

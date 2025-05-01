/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:09:54 by yrhandou          #+#    #+#             */
/*   Updated: 2025/05/01 14:50:05 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void free_arr(char **ptr)
{
	int i;

	if (!ptr)
		return;
	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}
 int ft_is_bonus_operator(char *str)
{
	int i = 0;
	char *operators[4] = {"&&", ">>", "<<", "||"};
	if (!str)
		return 0;
	while (i < 4)
	{
		if (ft_strncmp(str, operators[i], 2) == 0)
			return 1;
		i++;
	}
	return 0;
}
int ft_is_operator(int c)
{
	if (c == '|' || c == '>') // c == '||' || c == '&&' || c == '>>'|| c == '<<')
		return 1;
	else if(ft_is_bonus_operator((char *)&c))
		return 2;
	return 0;
}


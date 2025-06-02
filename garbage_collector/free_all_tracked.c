/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_tracked.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:06:00 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/01 12:06:22 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

void	free_all_tracked(void)
{
	t_gcnode	**tracker;
	t_gcnode	*tmp;

	tracker = memory_tracker();
	if (!tracker || !*tracker)
		return ;
	while (*tracker)
	{
		free((*tracker)->address);
		tmp = *tracker;
		*tracker = (*tracker)->next;
		free(tmp);
	}
}
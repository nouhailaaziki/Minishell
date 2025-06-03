/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_intro.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:15:38 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/03 15:55:21 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

void	display_intro(void)
{
	printf(ORANGE BOLD"➤  Welcome to the L33tShell ");
	printf("— your default interactive shell.\n"RESET);
	printf(BOLD"-------------------by noaziki");
	printf(" && yrhandou--------------------\n"RESET);
}
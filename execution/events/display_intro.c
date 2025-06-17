/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_intro.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:15:38 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/09 08:07:22 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void	display_intro(void)
{
	printf(ORANGE BOLD"➤  Welcome to the L33tShell ");
	printf("— your default interactive shell.\n"RESET);
	printf(BOLD"-------------------by noaziki");
	printf(" && yrhandou--------------------\n"RESET);
}

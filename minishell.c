/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:05:35 by noaziki           #+#    #+#             */
/*   Updated: 2025/05/04 12:08:54 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*head;

	head = NULL;
	(void)argc;
	fill_env_list(envp, &head);
	executor(argv, argc, &head);
}

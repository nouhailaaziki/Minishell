/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:29:12 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/03 21:15:29 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	pwd(t_stash *stash)
{
	char	*pwd;
	int		i;

	i = 0;
	pwd = getcwd(0, 0);
	if (!pwd)
	{
		pwd = na_strdup(stash->pwd_backup);
		if (!pwd)
			return (1);
		i = 1;
	}
	printf("%s\n", pwd);
	if (i == 0)
		free(pwd);
	return (0);
}

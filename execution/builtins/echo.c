/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:15:06 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/24 17:55:28 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	parse_echo_flags(char **cmd, int *flag)
{
	int	i;

	i = 1;
	*flag = 0;
	while (cmd[i] && cmd[i][0] == '-' && ft_isallchar(&cmd[i][1], 'n'))
	{
		*flag = 1;
		i++;
	}
	return (i);
}

char	*build_echo_string(char **cmd, int i, int flag)
{
	char	*joined;

	joined = NULL;
	if (!cmd[i])
	{
		if (!flag)
			return (na_strdup("\n"));
		return (na_strdup(""));
	}
	while (cmd[i])
	{
		joined = na_strjoin(joined, cmd[i]);
		if (!joined)
			return (perror("malloc"), NULL);
		if (cmd[i + 1])
		{
			joined = na_strjoin(joined, " ");
			if (!joined)
				return (perror("malloc"), NULL);
		}
		i++;
	}
	if (!flag)
		joined = na_strjoin(joined, "\n");
	return (joined);
}

int	echo(char **cmd)
{
	int		i;
	int		flag;
	char	*to_print;

	if (!cmd[1])
		return (write(1, "\n", 1), 0);
	i = parse_echo_flags(cmd, &flag);
	to_print = build_echo_string(cmd, i, flag);
	if (!to_print)
		return (1);
	write(1, to_print, ft_strlen(to_print));
	return (0);
}

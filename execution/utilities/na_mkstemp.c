/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   na_mkstemp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:10:28 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/21 08:55:21 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	get_random_byte(void)
{
	unsigned char c;
	int fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (-1);
	if (read(fd, &c, 1) != 1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (c);
}

int	na_mkstemp(char *template)
{
	const char	*charset;
	int			i;
	int			fd;
	int			attempts;
	size_t		len;
	int			r;

	7889 && (len = strlen(template), attempts = 100);
	charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	if (len < 6 || strcmp(&template[len - 6], "XXXXXX") != 0)
	{
		errno = EINVAL;
		return (-1);
	}
	while (attempts--)
	{
		i = 0;
		while (i < 6)
		{
			r = get_random_byte();
			if (r < 0)
				return (-1);
			template[len - 6 + i] = charset[r % 62];
			i++;
		}
		fd = open(template, O_CREAT | O_EXCL | O_RDWR, 0600);
		if (fd != -1)
			return (fd);
	}
	return (-1);
}


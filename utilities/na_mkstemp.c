/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   na_mkstemp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:10:28 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/29 12:14:04 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

int	get_random_byte(void)
{
	unsigned char	c;
	int				fd;

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

int	generate_random_filename(char *template, size_t len)
{
	const char	*charset;
	int			i;
	int			r;

	charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	i = 0;
	while (i < 6)
	{
		r = get_random_byte();
		if (r < 0)
			return (-1);
		template[len - 6 + i] = charset[r % 62];
		i++;
	}
	return (0);
}

int	validate_template(char *template, size_t len)
{
	if (len < 6 || ft_strcmp(&template[len - 6], "XXXXXX") != 0)
	{
		errno = EINVAL;
		return (-1);
	}
	return (0);
}

int	na_mkstemp(char *template, t_redir *redir)
{
	size_t		len;
	int			attempts;

	len = ft_strlen(template);
	attempts = 100;
	if (validate_template(template, len) == -1)
		return (-1);
	while (attempts--)
	{
		if (generate_random_filename(template, len) == -1)
			return (-1);
		redir->fd = open(template, O_CREAT | O_EXCL | O_RDWR, 0600);
		if (redir->fd != -1)
			return (redir->fd);
	}
	return (-1);
}

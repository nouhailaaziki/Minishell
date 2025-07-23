/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:06:54 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/20 18:50:11 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

bool	has_quoted_wildcard(const char *s)
{
	bool	in_single_quotes;
	bool	in_double_quotes;

	in_single_quotes = false;
	in_double_quotes = false;
	while (*s)
	{
		if (*s == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (*s == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (*s == '*' && (in_single_quotes || in_double_quotes))
			return (true);
		s++;
	}
	return (false);
}

bool	has_unquoted_wildcard(const char *s)
{
	bool	in_single_quotes;
	bool	in_double_quotes;

	in_single_quotes = false;
	in_double_quotes = false;
	while (*s)
	{
		if (*s == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (*s == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (*s == '*' && !in_single_quotes && !in_double_quotes)
			return (true);
		s++;
	}
	return (false);
}

char	*remove_quotes(const char *s)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	bool	in_single_quotes;
	bool	in_double_quotes;

	i = 0;
	j = 0;
	in_single_quotes = false;
	in_double_quotes = false;
	new_str = malloc(strlen(s) + 1);
	if (!new_str)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (s[i] == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else
			new_str[j++] = s[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*get_working_directory(t_stash *stash)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup(stash->pwd_backup);
	if (!pwd)
		perror("malloc");
	return (pwd);
}

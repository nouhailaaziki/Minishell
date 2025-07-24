/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:37:00 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/24 16:54:00 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

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
	new_str = malloc(ft_strlen(s) + 1);
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

void	process_character(char c, t_mask_state *state, char *new_str)
{
	if (c == '\'' && !state->in_double_quotes)
		state->in_single_quotes = !state->in_single_quotes;
	else if (c == '\"' && !state->in_single_quotes)
		state->in_double_quotes = !state->in_double_quotes;
	else
	{
		if (c == '*' && (state->in_single_quotes || state->in_double_quotes))
			new_str[state->j++] = 1;
		else
			new_str[state->j++] = c;
	}
}

char	*create_masked_pattern(const char *s)
{
	char			*new_str;
	size_t			i;
	t_mask_state	state;

	i = 0;
	state.in_single_quotes = false;
	state.in_double_quotes = false;
	state.j = 0;
	new_str = malloc(ft_strlen(s) + 1);
	if (!new_str)
		return (NULL);
	while (s[i])
	{
		process_character(s[i], &state, new_str);
		i++;
	}
	new_str[state.j] = '\0';
	return (new_str);
}

bool	contains_unquoted_wildcard(const char *s)
{
	bool	in_single;
	bool	in_double;

	in_single = false;
	in_double = false;
	while (*s)
	{
		if (*s == '\'' && !in_double)
			in_single = !in_single;
		else if (*s == '"' && !in_single)
			in_double = !in_double;
		else if (*s == '*' && !in_single && !in_double)
			return (true);
		s++;
	}
	return (false);
}

size_t	process_no_wildcard(char **cmd, size_t i)
{
	char	*pattern_no_quotes;

	pattern_no_quotes = remove_quotes(cmd[i]);
	if (!pattern_no_quotes)
	{
		perror("malloc");
		return (0);
	}
	free(cmd[i]);
	cmd[i] = pattern_no_quotes;
	return (1);
}

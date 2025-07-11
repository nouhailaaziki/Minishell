/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:49:47 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/11 20:42:18 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

static int	word_counter(char const *str)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]))
			i++;
		else
		{
			counter++;
			while (str[i] && !ft_isspace(str[i]))
				i++;
		}
	}
	return (counter);
}

static int	count_sub(char const *str)
{
	int	i;
	char quote;

	i = 0;
	quote = 0;
	while (str[i] && !ft_isspace(str[i]))
	{
		if(ft_isquote(str[i]))
		{
			quote = str[i++];
			i += in_quote_len(&str[i], quote);
			if(str[i])
				i++;
		}
		else
			i++;
	}
	return (i);
}

static char	**free_arr(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	return (NULL);
}

char	**ft_split_args(char const *s)
{
	int		i;
	int		j;
	char	**args;

	if (!s)
		return (NULL);
	args = (char **)ft_calloc(sizeof(char *) , (word_counter(s) + 1));
	if (!args)
		return (NULL);
	i = 0;
	j = -1;
	while (s[i] != '\0')
	{
		i += skip_spaces(&s[i]);
		args[++j] = ft_substr(s, i, count_sub(&s[i]));
		if (!args[j])
			return (free_arr(args));
		while (s[i] && !ft_isspace(s[i]))
			i++;
	}
	return (args[++j] = NULL, args);
}

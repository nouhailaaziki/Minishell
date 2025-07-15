/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:49:47 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/12 20:26:57 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

static int	word_counter(char *str)
{
	int		counter;
	int		i;
	char	quote;

	counter = 0;
	i = 0;
	while (str[i])
	{
		i += skip_spaces(&str[i]);
		if (!str[i])
			break ;
		counter++;
		if (ft_isquote(str[i]))
		{
			quote = str[i++];
			i += in_quote_len(&str[i], quote);
			if (str[i] == quote)
				i++;
		}
		else
			while (str[i] && !ft_isspace(str[i]))
				i++;
	}
	return (counter);
}

static int	count_sub_arg(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i] && !ft_isspace(str[i]))
	{
		if (ft_isquote(str[i]))
		{
			quote = str[i++];
			i += in_quote_len(&str[i], quote);
			if (str[i] == quote)
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

char	**ft_split_args(char *s)
{
	int		i;
	int		j;
	char	**args;
	int		arg_len;

	if (!s)
		return (NULL);
	args = ft_calloc(sizeof(char *), (word_counter(s) + 1));
	if (!args)
		return (NULL);
	i = 0;
	j = -1;
	while (s[i] != '\0')
	{
		i += skip_spaces(&s[i]);
		if (!s[i])
			break ;
		arg_len = count_sub_arg(&s[i]);
		args[++j] = ft_substr(s, i, arg_len);
		if (!args[j])
			return (free_arr(args));
		i += arg_len;
	}
	return (args[++j] = NULL, args);
}

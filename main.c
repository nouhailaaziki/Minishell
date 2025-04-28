/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:34:48 by yrhandou          #+#    #+#             */
/*   Updated: 2025/04/28 12:13:51 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// size_t token_counter(char *s)
// {
// 	size_t i;
// 	size_t j;
// 	size_t counter;
// 	char *delimiters;
// 	int *delimiters_counter;
// 	delimiters_counter = malloc(sizeof(int));
// 	if (delimiters)
// 		return 0;
// 	char *str;
// 	i = 0;
// 	j = 0;
// 	counter = 0;
// 	str = s;
// 	if (str[0] == ' ')
// 		str++;
// 	str = ft_strchr(str, ' ');
// 	if (!str)
// 		return 0;
// 	while (str)
// 	{
// 		counter++;
// 		str++;
// 		str = ft_strchr(str, ' ');
// 	}
// 	free(delimiters);
// 	return counter;
// }
// int lexer(char *str)
// {
// 	size_t i;
// 	size_t j;
// 	t_token *tokens;
// 	size_t token_count;
// 	token_count = 0;
// tokens = malloc(sizeof(t_token));
// if(!tokens)
// 	return 0;
// 	i = 0;
// 	j = 0;
// 	char **sub_tokens = ft_split(str, ' ');
// 	if (!sub_tokens)
// 		return 0;
// 	while (sub_tokens[i][j])
// 	{
// 		while (sub_tokens[i][j])
// 		{
// 			if (ft_isalpha(sub_tokens[i][j]))
// 				j++;
// 			else if (sub_tokens[i][0] == '-')
// 			{
// 				if (ft_isalpha(sub_tokens[i][j]))
// 				j++
// 			}
// 		}
// 		i++;
// 	}
// 	i++;
// 	token_count++;
// 	if (str[i] == '-')
// 	{
// 		while (ft_isalpha(str[i]))
// 			i++;
// 		token_count++;
// 	}
// 	while (str[i])
// 	{
// 		i++;
// 	}
// 	return i;
// }

int ft_strsquash(char *str)
{
	int i = 0;
	int s_len = 0;
	;

	while (str[i])
	{
		// ft_putnbr(s_len);
		if (!ft_isspace(str[i]))
		{
			s_len++;
			if (ft_isspace(str[i + 1]))
				s_len++;
		}
		i++;
	}
	char *s = ft_calloc(s_len + 1, sizeof(char));
	if (!s)
		return 0;
	return s_len;
}
char **token_slicer(char *str, int token_count)
{
	int i = 0;
	int j = 0;
	char *store;
	char *tmp;
	char *tmp2;
	int position = 0;
	if (!str)
		return NULL;
	char **token = ft_calloc(token_count, sizeof(char *));
	if (!token)
		return NULL;
	while (str[i])
	{
		if (ft_is_bonus_operator(&str[i]))
		{
			tmp = ft_substr(str, position, i - position);
			token[j++] = ft_strtrim(tmp, " ");
			position = i;
			token[j++] = ft_substr(str, position, 2);
			i += 2;
			position = i;
			free(tmp);
		}
		if (ft_is_operator(str[i]))
		{
			tmp = ft_substr(str, position, i - position);
			token[j++] = ft_strtrim(tmp, " ");
			position = i;
			token[j++] = ft_substr(str, position, 1);
			position = i + 1;
			free(tmp);
		}
		if (str[i + 1] == '\0')
		{
			tmp2 = ft_substr(str, position, i);
			token[j] = ft_strtrim(tmp2, " ");
			free(tmp2);
		}
		i++;
	}
	return token;
}

void f()
{
	system("leaks -q minishell");
}

int main(void)
{
	atexit(f);
	int i = 0;
	int j = 0;
	char *str = "ls      -al |       | ";
	int token_count = token_counter(str);
	char **tokens = token_slicer(str, token_count);
	printf(BLU "TOKEN COUNT : %d\n", token_count);
	// printf(BLU "squashed : %d\n", ft_strsquash(tokens[0]));
	while (i < token_count)
	{
		printf(GRN "token :  <%s>\n" RESET, tokens[i]);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

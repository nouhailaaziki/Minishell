/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:34:48 by yrhandou          #+#    #+#             */
/*   Updated: 2025/05/01 15:06:12 by yrhandou         ###   ########.fr       */
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

// int ft_strsquash(char *str)
// {
// 	int i = 0;
// 	int s_len = 0;
// 	;

// 	while (str[i])
// 	{
// 		if (!ft_isspace(str[i]))
// 		{
// 			s_len++;
// 			if (ft_isspace(str[i + 1]))
// 				s_len++;
// 		}
// 		i++;
// 	}
// 	char *s = ft_calloc(s_len + 1, sizeof(char));
// 	if (!s)
// 		return 0;
// 	return s_len;
// }
// char **token_slicer(char *str, int token_count)
// {
// 	int i = 0;
// 	int j = 0;
// 	char *store;
// 	char *tmp;
// 	char *tmp2;
// 	int position = 0;
// 	if (!str)
// 		return NULL;
// 	char **token = ft_calloc(token_count, sizeof(char *));
// 	if (!token)
// 		return NULL;
// 	while (str[i])
// 	{
// 		if (ft_is_bonus_operator(&str[i]))
// 		{
// 			tmp = ft_substr(str, position, i - position);
// 			token[j++] = ft_strtrim(tmp, " ");
// 			position = i;
// 			token[j++] = ft_substr(str, position, 2);
// 			i += 2;
// 			position = i;
// 		}
// 		if (ft_is_operator(str[i]))
// 		{
// 			tmp = ft_substr(str, position, i - position);
// 			token[j++] = ft_strtrim(tmp, " ");
// 			position = i;
// 			token[j++] = ft_substr(str, position, 1);
// 			position = i + 1;
// 			// free(tmp);
// 		}
// 		if (str[i + 1] == '\0')
// 		{
// 			tmp2 = ft_substr(str, position, i);
// 			token[j] = ft_strtrim(tmp2, " ");
// 			// free(tmp2);
// 		}
// 		i++;
// 	}
// 	return token;
// }

char *ft_op_srchr(char *s)
{
	int i = 0;
	char *set[4] = {"||", "&&", ">>", "<<"};
	while (i<=3)
	{
		if (ft_strnstr(s, set[i], 2))
			return &s[i];
		i++;
	}
	puts("hi");
	return NULL;
}

int token_counter(char *str)
{
	int i;
	int j;
	int token_count;

	token_count = 0;
	if (!str)
		return 0;
	i = 0;
	while (str[i])
	{
		if (ft_is_operator(str[i]))
			token_count++;
		i++;
	}

	return token_count;
}
// char **token_slicer_v2(char *str, int token_count)
// {
// 	int i = 0;
// 	int token_length = 0;
// 	int position = 0;
// 	char **tokens = ft_calloc(token_count, sizeof(char *));
// 	if (!tokens)
// 		return NULL;
// 	while (str[i])
// 	{
// 		token_length = 0;
// 		while (str[i] != '\0' && !ft_is_operator(str[i]))
// 		{
// 			token_length++;
// 			i++;
// 		}
// 		tokens[position++] = ft_substr(str, i - token_length, token_length);
// 		tokens[position++] = ft_substr(str, i, ft_is_operator(str[i]));
// 		token_count -= 2;
// 		if (!str[i] || token_count == 0)
// 			break;
// 		i++;
// 	}
// }

int main(void)
{
	int i = 0;
	int j = 0;
	char *str = "ls -al | grep | p";
	int token_count = token_counter(str);
	ft_printf(BLU "TOKEN COUNT : %d\n", token_count);
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:34:48 by yrhandou          #+#    #+#             */
/*   Updated: 2025/04/26 21:59:28 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "coreutils/libft.h"

int ft_is_operator(int c)
{
	if (c == '|' || c  == '>') // || c == '||' || c == '>>'|| c == '<<'|| c == '&&')
		return 1;
	return 0;
}



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

int token_counter(char *str)
{
	int i = 0;
	int j = 0;
	char *store;
	if (!str)
		return 0;
	int token_count = 1;
	while (str[i])
	{
		if (ft_is_operator(str[i]))
		{
			token_count++;
			if (str[i + 1] != '\0')
				token_count++;
		}
		i++;
	}
	return token_count;
}

char **token_slicer(char *str, int token_count)
{
	int i = 0;
	int j = 0;
	char *store;
	int position = 0;
	if (!str)
		return NULL;
	char **token = malloc(token_count * sizeof(char *));
	if(!token)
		return NULL;
	while (str[i])
	{
		if (ft_is_operator(str[i]))
		{
			token[j++] = ft_strtrim(ft_substr(str, position,i)," ");
			position = i;
			if(str[i+1] != '\0')
				token[j++] = ft_substr(str,position++,1);
		}
		if(str[i+1] == '\0')
			token[j] = ft_strtrim(ft_substr(str, position, i), " ");
		i++;
	}
	return token;
}

int main(void)
{
	int i = 0;
	int j = 0;
	char *str = "ls -al | echo hola";
	int token_count=  token_counter(str);
	char **tokens = token_slicer(str, token_count);
	// while (tokens[i])
		printf("count :  <%d>\n", token_count);
		printf("token :  <%s>\n", tokens[0]);
		printf("token :  <%s>\n", tokens[1]);
		printf("token :  <%s>\n", tokens[2]);
}

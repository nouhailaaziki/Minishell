/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:34:48 by yrhandou          #+#    #+#             */
/*   Updated: 2025/04/21 19:39:13 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "coreutils/libft.h"

size_t token_counter(char *s)
{
	size_t i;
	size_t j;
	size_t counter;
	char * delimiters;

	delimiters = "";
	int *delimiters_counter;

	delimiters_counter = malloc(sizeof(int));
	if(delimiters)
		return 0;
	char *str;
	i = 0;
	j = 0;
	counter = 0;
	str = s;
	if (str[0] == ' ')
		str++;
	str = ft_strchr(str, ' ');
	if (!str)
		return 0;
	while (str)
	{

		counter++;
		str++;
		str = ft_strchr(str, ' ');
	}
	free(delimiters);
	return counter;
}

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

int main(void)
{
	char *str;

	printf("%zu\n", token_counter(" ls -al | grep '.' > txtfile"));
}

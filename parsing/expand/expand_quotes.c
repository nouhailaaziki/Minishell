/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:13:43 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/10 10:37:11 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int in_quote_len(char *str, char quote)
{
	int i;

	i = 0;
 	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

int in_quote_fill(char *old_cmd,char **new_cmd,  char quote)
{
	int i;

	i = 0;
 	while (old_cmd[i] && old_cmd[i] != quote)
	{
		**new_cmd = old_cmd[i];
		(*new_cmd)++;
		i++;
	}
	return (i);
}

static void count_inquote(char *old_cmd , int *count)
{
    int		j;
    char	quote;

	j = 0;
    if (!old_cmd)
        return ;
    while (old_cmd[j])
    {
        if (ft_isquote(old_cmd[j]))
        {
            quote = old_cmd[j++];
			*count += in_quote_len(&old_cmd[j], quote);
			j += in_quote_len(&old_cmd[j], quote);
            if (old_cmd[j] == quote)
			{
                quote = 0;
				j++;
			}
        }
        else
		{
            (*count)++;
			j++;
		}
    }
}
static void	fill_quote_content(char *old_cmd, char **new_cmd)
{
    int		j;
    char	quote;
	char* 	cmd_pos;

	j = 0;
	cmd_pos = *new_cmd;
    while (old_cmd[j])
    {
        if (ft_isquote(old_cmd[j]))
        {
            quote = old_cmd[j++];
			j += in_quote_fill(&old_cmd[j],&cmd_pos, quote);
            if (old_cmd[j] == quote)
			{
                quote = 0;
				j++;
			}
		}
        else
			*cmd_pos++ = old_cmd[j++];
    }
	*cmd_pos = '\0';
}

void expand_quotes(char **old_cmd)
{
	int count;
	char *new_cmd;

	count = 0;
	if(!old_cmd || !*old_cmd)
		return;
	count_inquote(*old_cmd, &count);
	new_cmd = ft_calloc( count +1 ,sizeof(char));
	if(!new_cmd)
		return;
	fill_quote_content(*old_cmd, &new_cmd);
	// free(*old_cmd);
	*old_cmd = new_cmd;
}

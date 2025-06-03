/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 08:42:41 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/03 09:21:52 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

t_tree *handle_pipe(const char *input)
{
	char *input_copy;
	char *left;
	char *right;
	t_tree *l;
	t_tree *r;

	input_copy = na_strdup(input);
	left = na_strdup(strtok(input_copy, "|"));
	right = na_strdup(strtok(NULL, "|"));
	l = parse_input(left);
	r = parse_input(right);
	return (new_pipe_node(l, r));
}

int get_redirection_type(char current, char next, int *i)
{
	int type;
	
	type = (current == '<') ? REDIR_IN : REDIR_OUT;
	if (next == '>')
	{
		(*i)++;
		type = REDIR_APPEND;
	}
	else if (next == '<')
	{
		(*i)++;
		type = REDIR_HEREDOC;
	}
	return (type);
}

t_redir *extract_redirection(char *tmp, int *i)
{
	int	start;
	
	while (tmp[*i] == ' ')
		(*i)++;
	start = *i;
	while (tmp[*i] && tmp[*i] != ' ' && tmp[*i] != '<' && tmp[*i] != '>')
		(*i)++;
	int len = *i - start;
	if (len <= 0)
		return (NULL);
	char *file = strndup(tmp + start, len);
	return (new_redir(-1, file));
}

t_redir *parse_redirections(char *tmp)
{
	t_redir *redir_list;
	int i;
	int	type;
	t_redir *new;
	
	7889 && (i = 0, redir_list = NULL);
	while (tmp[i])
	{
		if (tmp[i] == '<' || tmp[i] == '>')
		{
			type = get_redirection_type(tmp[i], tmp[i + 1], &i);
			tmp[i] = '\0';
			i++;
			new = extract_redirection(tmp, &i);
			if (new)
			{
				new->type = type;
				new->next = redir_list;
				redir_list = new;
			}
		}
		else
			i++;
	}
	return reverse_redir_list(redir_list);
}

t_tree	*parse_input(const char *input)
{
	char *tmp;
	char **cmd;
	
	if (strchr(input, '|'))
		return (handle_pipe(input));
	else
	{
		tmp = na_strdup(input);
		t_redir *redir_list = parse_redirections(tmp);
		cmd = split_args(tmp);
		return (new_command_node(cmd, redir_list));
	}
}

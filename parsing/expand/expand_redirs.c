/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 06:13:39 by yrhandou          #+#    #+#             */
/*   Updated: 2025/07/14 13:44:55 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void expand_redirs(t_redir **head, t_env **env, int stash_status)
{
	t_redir *current;
	t_var *keys;
	char *tmp;

	keys = NULL;
	current = *head;
	while (current)
	{
		if(current->type != REDIR_HEREDOC)
		{
			tmp = expand_vars(&current->file, env, stash_status);
			expand_quotes(&tmp);
			if (!ft_strcmp(tmp, "") || multi_str_included(tmp))
				current->is_ambiguous = 1;
			current->file = tmp;
		}
		current = current->next;
	}
}

int translation_check(char *current)
{
	int i;

	i = 0;
	while(current[i])
	{

		i++;
	}
	return 0;
}

void	expand_heredoc(t_redir **head)
{
	t_redir *current;
	t_var *keys;

	keys = NULL;
	current = *head;
	while (current && current->type == REDIR_HEREDOC)
	{
		// if(translation_check(current->file))
			// do_something();
		current->flag = expand_quotes(&current->file);
		current = current->next;
	}
}



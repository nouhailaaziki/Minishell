/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:14:39 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/21 10:31:42 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

void open_heredoc(t_redir *redir, t_stash *stash)
{
    char *line;
    char *store;

    store = NULL;
    while (1)
    {
        line = readline("> ");
        if (!line)
            break;
        if (ft_strcmp(line, redir->file) == 0)
        {
            free(line);
            break;
        }
        store = na_strjoin(store, line);
        store = na_strjoin(store, "\n");
        free(line);
    }
    ft_strlcpy(stash->heredoc_store, "/tmp/.tmpXXXXXX", sizeof(stash->heredoc_store));
    redir->fd = na_mkstemp(stash->heredoc_store);
    if (redir->fd == -1)
        return (perror("na_mkstemp"));
    write(redir->fd, store, ft_strlen(store));
    close (redir->fd);
    redir->fd = open(stash->heredoc_store, O_RDONLY, 0600);
    if (redir->fd == -1)
        return (perror("reopen"));
}

int	check_heredoc(t_redir *redir, t_stash *stash)
{
	if (!redir)
		return (1);
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			open_heredoc(redir, stash);
			if (redir->fd == -1)
				return (1);
			else
				unlink(stash->heredoc_store);
		}
		redir = redir->next;
	}
	return (0);
}

int	count_heredocs(t_tree *ast)
{
	int	counter;
	t_redir *redir;

	counter = 0;
	if (!ast)
		return (0);
	if (ast->type == NODE_COMMAND)
	{
		redir = ast->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
				counter++;
			redir = redir->next;
		}
	}
	counter += count_heredocs(ast->left);
	counter += count_heredocs(ast->right);
	return (counter);
}

int manage_heredoc(t_tree *ast, t_redir *redir, t_stash *stash)
{
    if (count_heredocs(ast) > 16)
    {
        write(2, "L33tShell: maximum here-document count exceeded\n", 49);
        exit (1);
    }
    return (check_heredoc(redir, stash));
}
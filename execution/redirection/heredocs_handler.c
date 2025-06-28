/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:14:39 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/26 11:34:52 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	process_heredoc_line(t_redir *redir, char **store, t_stash *stash)
{
	char	*line;

	disable_echoctl(stash);
	line = readline("> ");
	restore_terminal(stash);
	if (g_sigint_received)
	{
		if (line)
			free(line);
		stash->heredoc_interrupted = 1;
		return (1);
	}
	if (!line || ft_strcmp(line, redir->file) == 0)
	{
		if (line)
			free(line);
		return (1);
	}
	*store = na_strjoin(*store, line);
	*store = na_strjoin(*store, "\n");
	free(line);
	return (0);
}

int	fill_file(t_redir *redir, t_stash *stash)
{
	char	*store;

	store = NULL;
	while (1)
	{
		if (process_heredoc_line(redir, &store, stash))
			break ;
	}
	if (store && !g_sigint_received)
		write(redir->fd_wr, store, ft_strlen(store));
	return (stash->heredoc_interrupted);
}

int	setup_heredoc_file(t_redir *redirs, t_stash *stash)
{
	stash->heredoc_store = na_strdup("/tmp/.l33tshell-XXXXXX");
	if (!stash->heredoc_store)
		return (perror("malloc"), 1);
	redirs->fd_wr = na_mkstemp(stash->heredoc_store, redirs);
	if (redirs->fd_wr == -1)
		return (1);
	redirs->fd_rd = open(stash->heredoc_store, O_RDONLY);
	if (redirs->fd_rd == -1)
	{
		close(redirs->fd_wr);
		return (1);
	}
	unlink(stash->heredoc_store);
	stash->heredoc_store = NULL;
	return (0);
}

int	process_single_heredoc(t_redir *redirs, t_stash *stash)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		status = fill_file(redirs, stash);
		close(redirs->fd_wr);
		close(redirs->fd_rd);
		exit(status);
	}
	close(redirs->fd_wr);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		stash->heredoc_interrupted = 1;
		return (1);
	}
	return (WEXITSTATUS(status));
}

int	open_heredocs(t_redir *redir, t_stash *stash)
{
	t_redir	*current;

	current = redir;
	while (current && current->type)
	{
		if (current->type == REDIR_HEREDOC)
		{
			if (setup_heredoc_file(current, stash) != 0)
				return (1);
			if (process_single_heredoc(current, stash) != 0)
			{
				close(current->fd_rd);
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}

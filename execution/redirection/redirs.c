/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:59:03 by noaziki           #+#    #+#             */
/*   Updated: 2025/07/23 12:00:42 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	apply_fd_redirection(t_redir *redir, int fd, t_stash *stash)
{
	if (fd == -1 && !stash->is_parent_flag)
		exit (puterror(1, redir->file, NULL,
				na_strjoin(": ", strerror(errno))));
	else if ((fd == -1 && stash->is_parent_flag))
		return (puterror(1, redir->file, NULL,
				na_strjoin(": ", strerror(errno))), -1);
	if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (puterror(1, "dup2", NULL, ": failed"));
	}
	if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (puterror(1, "dup2", NULL, ": failed"));
	}
	close(fd);
	return (0);
}

int	init_fd(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == REDIR_OUT)
		fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (redir->type == REDIR_IN)
		fd = open(redir->file, O_RDONLY);
	return (fd);
}

char	*expand_heredoc_line(char *line, t_stash *stash)
{
	char	*expanded_line;

	expanded_line = expand_vars(&line, stash->env_list, stash->status, 1);
	return (expanded_line);
}

int	expand_heredoc_and_get_fd(t_redir *redir, t_stash *stash)
{
	int		expanded_fd;
	char	*line;
	char	*expanded_line;
	char	*filename;

	filename = na_strdup("/tmp/.L33tShell-XXXXXX");
	if (!filename)
		return (perror("malloc"), -2);
	expanded_fd = na_mkstemp(filename, redir);
	if (expanded_fd == -1)
		return (-1);
	line = get_next_line(redir->fd_rd);
	while (line)
	{
		if (redir->flag == 0)
		{
			expanded_line = expand_heredoc_line(line, stash);
			write(expanded_fd, expanded_line, ft_strlen(expanded_line));
		}
		if (redir->flag == 1)
			write(expanded_fd, line, ft_strlen(line));
		line = get_next_line(redir->fd_rd);
	}
	(close(expanded_fd), expanded_fd = open(filename, O_RDONLY));
	return (unlink(filename), expanded_fd);
}

int	handle_redirs(t_redir *redir, t_stash *stash)
{
	int	fd;

	if (!redir)
		return (0);
	while (redir)
	{
		if (redir->is_ambiguous && !stash->is_parent_flag)
			exit (puterror(1, redir->file, NULL, ": ambiguous redirect"));
		if (redir->is_ambiguous && stash->is_parent_flag)
			return (puterror(1, redir->file, NULL, ": ambiguous redirect"), -1);
		if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND
			|| redir->type == REDIR_IN)
			fd = init_fd(redir);
		else if (redir->type == REDIR_HEREDOC)
			fd = expand_heredoc_and_get_fd(redir, stash);
		else
		{
			redir = redir->next;
			continue ;
		}
		if (apply_fd_redirection(redir, fd, stash) == -1)
			return (1);
		redir = redir->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:59:03 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/28 13:34:02 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int	apply_fd_redirection(t_redir *redir, int fd)
{
	if (fd == -1)
		exit (puterror(1, redir->file, NULL, ": No such file or directory"));
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
	else if (redir->type == REDIR_HEREDOC)
		fd = redir->fd_rd;
	return (fd);
}

int	handle_redirs(t_redir *redir)
{
	int	i;
	int	fd;

	i = 0;
	if (!redir)
		return (1);
	while (redir)
	{
		if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND
			|| redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			fd = init_fd(redir);
		else
		{
			redir = redir->next;
			continue ;
		}
		if (apply_fd_redirection(redir, fd) == -1)
			i = 1;
		redir = redir->next;
	}
	return (i);
}

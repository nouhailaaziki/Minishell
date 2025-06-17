/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:59:03 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/17 12:59:56 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../launchpad.h"

int	handle_heredoc(t_redir *redir)
{
	char	*line;
	int		fd;

	fd = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc: open");
		return (-1);
	}
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
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	fd = open(".tmp", O_RDONLY);
	if (fd < 0)
	{
		perror("heredoc: reopen");
		return (-1);
	}
	return (fd);
}

int	apply_fd_redirection(t_redir *redir, int fd)
{
	if (fd == -1)
		exit (puterror(redir->file, ": No such file or directory"));
	if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (puterror("dup2", " failed"));
	}
	if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (puterror("dup2", " failed"));
	}
	close(fd);
	return (0);
}

int	handle_redirs(t_redir *redir)
{
	int	i;

	i = 0;
	if (!redir)
		return (1);
	while (redir)
	{
		if (redir->type == REDIR_OUT)
			redir->fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (redir->type == REDIR_APPEND)
			redir->fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (redir->type == REDIR_IN)
			redir->fd = open(redir->file, O_RDONLY);
		else if (redir->type == REDIR_HEREDOC)
		{
			redir->fd = handle_heredoc(redir);
			if (redir->fd == -1)
				return (1);
			else
				unlink(".tmp");
		}
		else
		{
			redir = redir->next;
			continue;
		}
		if(apply_fd_redirection(redir, redir->fd) == -1)
			i = 1;
		redir = redir->next;
	}
	return (i);
}



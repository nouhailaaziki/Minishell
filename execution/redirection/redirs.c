/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:59:03 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/09 08:07:22 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../launchpad.h"

int	handle_redirs(t_redir *redir)
{
	int		fd;

	while (redir)
	{
		if (!redir->file || redir->file[0] == '\0')
		{
			puterror("ambiguous redirect", NULL);
			return (1);
		}
		if (redir->type == REDIR_OUT)
			fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (redir->type == REDIR_APPEND)
			fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			fd = open(redir->file, O_RDONLY);
		else
		{
			redir = redir->next;
			continue;
		}
		if (fd == -1)
			exit(puterror(redir->file, ": No such file or directory"));
		if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
	exit (0);
}


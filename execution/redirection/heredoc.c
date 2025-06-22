/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:14:39 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/22 16:18:39 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int open_heredoc(t_redir *redir)
{
    char *line;
    char *store;
    int  temp_fd;
    char filename[] = "/tmp/.l33tshell-XXXXXX";

    store = NULL;
    while (1)
    {
        line = readline("> ");
        if (g_sigint_received)
        {
            if (line)
                free(line);
            free(store);
            return (1);
        }
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
    temp_fd = na_mkstemp(filename);
    if (temp_fd == -1)
        return (perror("na_mkstemp"), 1);
        if (store)
        write(temp_fd, store, ft_strlen(store));
    free(store);
    unlink(filename);
    lseek(temp_fd, 0, SEEK_SET);
    redir->fd = temp_fd;
    return (0);
}

int check_heredocs(t_redir *redir, t_stash *stash)
{
    int pid;
    int status;

    if (!redir)
        return (1);
    pid = fork();
    if (!pid)
    {
        signal(SIGINT, SIG_DFL);
        while (redir)
        {
            if (redir->type == REDIR_HEREDOC)
            {
                open_heredoc(redir);
                if (redir->fd == -1)
                    return (1);
                else
                    unlink(stash->heredoc_store);
            }
            redir = redir->next;
        }
        exit(0);
    }
    signal(SIGINT, SIG_IGN);
    wait(&status);
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
    {
        write(1, "\n", 1);
        stash->status = 1;
        return (stash->status);
    }
    return (0);
}

int manage_heredocs(t_tree *ast)
{
    t_redir *redir;

    if (!ast)
        return (0);
    if (ast->type == NODE_COMMAND)
    {
        redir = ast->redirs;
        while (redir)
        {
            if (redir->type == REDIR_HEREDOC)
            {
                if (open_heredoc(redir) != 0)
                {
                    return (1);
                }
            }
            redir = redir->next;
        }
    }
    if (manage_heredocs(ast->left) != 0) return (1);
    if (manage_heredocs(ast->right) != 0) return (1);
    return (0);
}

void count_heredocs(t_tree *ast)
{
    int counter;
    t_redir *redir;

    counter = 0;
    if (ast && ast->type == NODE_COMMAND)
    {
        redir = ast->redirs;
        while (redir && redir->type)
        {
            if (redir->type == REDIR_HEREDOC)
                counter++;
            redir = redir->next;
        }
    }
    if (counter > 16)
    {
        write(2, "L33tShell: maximum here-document count exceeded\n", 49);
        exit(1);
    }
    if (ast->left)
        count_heredocs(ast->left);
    if (ast->right)
        count_heredocs(ast->right);
}

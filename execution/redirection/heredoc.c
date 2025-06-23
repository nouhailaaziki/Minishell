/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:14:39 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/23 08:57:14 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

int fill_file(t_redir *redir, t_stash *stash)
{
    char *line;
    char *store;
    
    store = NULL;
    while (1)
    {
        disable_echoctl();
        line = readline("> ");
        restore_terminal();
        if (g_sigint_received)
        {
            if (line)
                free(line);
            stash->heredoc_interrupted = 1;
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
    if (store && !g_sigint_received)
        write(redir->fd_WR, store, ft_strlen(store));
    return (0);
}

int open_heredocs(t_redir *redir, t_stash *stash)
{
    t_redir *redirs = redir;
    int status;
    pid_t pid;

    while (redirs && redirs->type)
    {
        if (redirs->type == REDIR_HEREDOC)
        {
            stash->heredoc_store = na_strdup("/tmp/.l33tshell-XXXXXX");
            if (!stash->heredoc_store)
                return (perror("malloc"), 1);
            redirs->fd_WR = na_mkstemp(stash->heredoc_store);
            if (redirs->fd_WR == -1)
                return (1);
            redirs->fd_RD = open(stash->heredoc_store, O_RDONLY);
            if (redirs->fd_RD == -1)
                return (1);
            unlink(stash->heredoc_store);
            pid = fork();
            if (pid == -1)
                return (perror("fork"), 1);
            if (pid == 0)
            {
                signal(SIGINT, SIG_DFL);
                status = fill_file(redirs, stash);
                close(redirs->fd_WR);
                exit(status);
            }
            close(redirs->fd_WR);
            signal(SIGINT, SIG_IGN);
            waitpid(pid, &status, 0);
            if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
            {
                write(1, "\n", 1);
                stash->heredoc_interrupted = 1;
                return (1);
            }
            if (WEXITSTATUS(status))
                return (1);
        }
        redirs = redirs->next;
    }
    return (0);
}

void manage_heredocs(t_tree *ast, t_stash *stash)
{
    if (!ast || stash->heredoc_interrupted)
        return;
    if (ast->type == NODE_COMMAND)
    {
        t_redir *redir = ast->redirs;
        int counter = 0;
        while (redir && redir->type)
        {
            if (redir->type == REDIR_HEREDOC)
                counter++;
            redir = redir->next;
        }
        if (counter > 0)
        {
            if (open_heredocs(ast->redirs, stash) != 0)
            {
                stash->status = 1;
                return;
            }
        }
    }
    if (ast->left)
        manage_heredocs(ast->left, stash);
    if (ast->right)
        manage_heredocs(ast->right, stash);
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
        exit(2);
    }
    if (ast->left)
        count_heredocs(ast->left);
    if (ast->right)
        count_heredocs(ast->right);
}

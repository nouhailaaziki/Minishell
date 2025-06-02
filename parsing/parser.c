/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:10:04 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/02 12:58:28 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

static t_redir_type get_redir_type(t_token *token)
{
    if (!token)
        return REDIR_NONE;
    if (strcmp(token->value, "<") == 0)
        return REDIR_IN;
    if (strcmp(token->value, ">") == 0)
        return REDIR_OUT;
    if (strcmp(token->value, ">>") == 0)
        return REDIR_APPEND;
    if (strcmp(token->value, "<<") == 0)
        return REDIR_HEREDOC;
    return REDIR_NONE;
}

static t_redir *parse_redirections(t_token **tokens)
{
    t_redir *head = NULL;
    t_redir *tail = NULL;

    while (*tokens)
    {
        t_redir_type type = get_redir_type(*tokens);
        if (type == REDIR_NONE)
            break;

        // t_token *redir_token = *tokens;
        *tokens = (*tokens)->next;

        if (!*tokens || (*tokens)->type != TOKEN_WORD)
        {
            // Handle syntax error
            return NULL;
        }

        t_redir *new = calloc(1, sizeof(t_redir));
        new->type = type;
        new->file = strdup((*tokens)->value);

        if (!head)
            head = new;
        else
            tail->next = new;
        tail = new;

        *tokens = (*tokens)->next;
    }

    return head;
}

static char **parse_arguments(t_token **tokens)
{
    // Count arguments first
    size_t count = 0;
    t_token *tmp = *tokens;
    while (tmp && tmp->type == TOKEN_WORD)
    {
        count++;
        tmp = tmp->next;
    }

    char **args = calloc(count + 1, sizeof(char *));
    if (!args)
        return NULL;

    for (size_t i = 0; i < count; i++)
    {
        args[i] = strdup((*tokens)->value);
        *tokens = (*tokens)->next;
    }

    return args;
}


static t_tree *parse_command(t_token **tokens)
{
    t_tree *node = calloc(1, sizeof(t_tree));
    if (!node)
        return NULL;

    node->type = NODE_COMMAND;
    node->redirs_before = parse_redirections(tokens);
    node->cmd = parse_arguments(tokens);
    node->redirs_after = parse_redirections(tokens);
    return node;
}

static t_tree *parse_command(t_token **tokens);
static t_redir *parse_redirections(t_token **tokens);
static char **parse_arguments(t_token **tokens);

t_tree *parse_input(t_token **tokens)
{
    // This assumes you already have a lexer that gives token list
    if (!tokens || !*tokens)
        return NULL;

    return parse_command(tokens);
}

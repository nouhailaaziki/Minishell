/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:08:00 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/03 09:49:19 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

static t_token  *new_token(t_token_type type, const char *value)
{
    t_token *token = malloc(sizeof(t_token));
    token->type = type;
    token->value = strdup(value);
    token->next = NULL;
    return token;
}

static void add_token(t_token **head, t_token **tail, t_token *new)
{
    if (!*head)
        *head = new;
    else
        (*tail)->next = new;
    *tail = new;
}

static int  is_operator_char(char c)
{
    return (c == '<' || c == '>' || c == '&' || c == '|' || c == '(' || c == ')');
}

static const char   *parse_operator(const char *input, char *buf)
{
    if (input[0] == '<' && input[1] == '<')
        return strncpy(buf, "<<", 3), input + 2;
    if (input[0] == '>' && input[1] == '>')
        return strncpy(buf, ">>", 3), input + 2;
    if (input[0] == '&' && input[1] == '&')
        return strncpy(buf, "&&", 3), input + 2;
    if (input[0] == '|' && input[1] == '|')
        return strncpy(buf, "||", 3), input + 2;
    buf[0] = *input;
    buf[1] = '\0';
    return input + 1;
}

t_token *lexer(const char *input)
{
    t_token *head = NULL, *tail = NULL;

    while (*input)
    {
        while (isspace(*input))
            input++;

        if (*input == '\0')
            break;

        if (is_operator_char(*input))
        {
            char op[3] = {0};
            input = parse_operator(input, op);

            t_token_type type = TOKEN_INVALID;
            if (strcmp(op, "|") == 0) type = TOKEN_PIPE;
            else if (strcmp(op, "||") == 0) type = TOKEN_OR;
            else if (strcmp(op, "&&") == 0) type = TOKEN_AND;
            else if (strcmp(op, "<") == 0 || strcmp(op, "<<") == 0 ||
                     strcmp(op, ">") == 0 || strcmp(op, ">>") == 0)
                type = TOKEN_REDIR;
            else if (strcmp(op, "(") == 0) type = TOKEN_PAREN_LEFT;
            else if (strcmp(op, ")") == 0) type = TOKEN_PAREN_RIGHT;

            add_token(&head, &tail, new_token(type, op));
        }
        else
        {
            // Simple word
            const char *start = input;
            while (*input && !isspace(*input) && !is_operator_char(*input))
                input++;

            char *word = strndup(start, input - start);
            add_token(&head, &tail, new_token(TOKEN_WORD, word));
            free(word);
        }
    }

    add_token(&head, &tail, new_token(TOKEN_EOF, ""));
    return head;
}

void    free_tokens(t_token *tokens)
{
    while (tokens)
    {
        t_token *next = tokens->next;
        free(tokens->value);
        free(tokens);
        tokens = next;
    }
}

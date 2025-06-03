/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:05:35 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/03 09:50:07 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

void	print_redirs(t_redir *redir)
{
	while (redir)
	{
		printf("Redir type: ");
		if (redir->type == REDIR_IN)
			printf("REDIR_IN");
		else if (redir->type == REDIR_OUT)
			printf("REDIR_OUT");
		else if (redir->type == REDIR_APPEND)
			printf("REDIR_APPEND");
		else if (redir->type == REDIR_HEREDOC)
			printf("REDIR_HEREDOC");
		else
			printf("UNKNOWN");
		printf(", file: %s\n", redir->file);
		redir = redir->next;
	}
}

void	print_ast(t_tree *node)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
	{
		printf("NODE_COMMAND: ");
		for (int i = 0; node->cmd && node->cmd[i]; i++)
			printf("%s ", node->cmd[i]);
		printf("\n");
		if (node->redirs)
		{
			printf("Redirections:\n");
			print_redirs(node->redirs);
		}
	}
	else if (node->type == NODE_PIPE)
	{
		printf("NODE_PIPE:\n");
		print_ast(node->left);
		print_ast(node->right);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	t_token	*tokens;
	t_tree	*ast;
	t_redir	*redir;
	char	*line;

	(void)argc, (void)argv;
	7889 && (env_list = NULL, tokens = NULL, ast = NULL);
	printf(ORANGE BOLD"➤  Welcome to the L33tShell ");
	printf("— your default interactive shell.\n"RESET);
	build_env(&env_list, envp);
	while (1)
	{
		line = readline(PINK BOLD"╰┈➤ L33tShell-N.Y ✗ "RESET);
		if (!line)
			break ;
		if (*line)
			add_history(line);
		tokens = lexer(line);
		if (!tokens)
			continue ;
		ast = parse_input(line);
		redir = ast->redirs;
		print_redirs(redir);
		// executor(ast, &env_list);
		free_tokens(tokens);
		free(line);
	}
	return (0);
}

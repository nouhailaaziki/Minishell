/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaziki <noaziki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:05:35 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/02 14:05:41 by noaziki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launchpad.h"

int main(int argc, char **argv, char **envp)
{
	t_env *env_list = NULL;
	t_token *tokens = NULL;
	t_tree *ast = NULL;
	char *line;

	(void)argc;
	(void)argv;
	printf(ORANGE BOLD"➤  Welcome to the L33tShell ");
	printf("— your default interactive shell.\n"RESET);	
	build_env(&env_list, envp);
	while (1)
	{
		line = readline(PINK BOLD"╰┈➤ L33tShell-N.Y ✗ "RESET);
		if (!line)
			break;
		if (*line)
			add_history(line);
		tokens = lexer(line);
		if (!tokens)
			continue;
		ast = parse_input(&tokens);
		if (!ast)
		{
			fprintf(stderr, "Parse error\n");
			continue;
		}
		executor(ast, &env_list);
		free_tokens(tokens);
		free(line);
	}
	return (0);
}

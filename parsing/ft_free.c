/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:08:57 by yrhandou          #+#    #+#             */
/*   Updated: 2025/06/28 11:44:47 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launchpad.h"

/**
* @brief Free The redirections of the Linked List
* @param redirs
*/
void	free_redirs(t_redir **redirs)
{
	t_redir	*next;
	t_redir	*tmp;

	if (!redirs || !*redirs)
		return ;
	tmp = *redirs;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->file)
			free(tmp->file);
		tmp->file = NULL;
		free(tmp);
		tmp = next;
	}
	(*redirs) = NULL;
}

/**
 * @brief Free the tree's 2d Array of strings
 * @param cmd : Command
 */
void	free_cmd(char **cmd)
{
	int	count;

	if (!cmd)
		return ;
	count = 0;
	while (cmd[count])
	{
		free(cmd[count]);
		cmd[count] = NULL;
		count++;
	}
	free(cmd[count]);
	cmd[count] = NULL;
	free(cmd);
}

/**
 * @brief Free the tree nodes Recursively
 * @param ast tree param
 */
void	free_tree(t_tree **ast)
{
	if (!(*ast) || !ast)
		return ;
	free_redirs(&(*ast)->redirs);
	free_cmd((*ast)->cmd);
	if ((*ast)->left)
		free_tree(&(*ast)->left);
	if ((*ast)->right)
		free_tree(&(*ast)->right);
	free((*ast));
	(*ast) = NULL;
}

void	clear_memory(t_shell *shell)
{
	if (shell->ast)
		free_tree(&shell->ast);
	if (shell->tokens)
		free_tokens(&shell->tokens);
	free(shell->line);
	shell->line = NULL;
}

void	free_tokens(t_token **head)
{
	t_token	*current;
	t_token	*next;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		if (current->value)
		{
			free(current->value);
			current->value = NULL;
		}
		current->type = 0;
		current->position = -1;
		current->next = NULL;
		current->prev = NULL;
		free(current);
		current = next;
	}
	*head = NULL;
}

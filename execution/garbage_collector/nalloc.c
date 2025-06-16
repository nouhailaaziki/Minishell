/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nalloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:09:05 by noaziki           #+#    #+#             */
/*   Updated: 2025/06/09 08:07:22 by yrhandou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../launchpad.h"

t_gcnode	**memory_tracker(void)
{
	static t_gcnode	*root = NULL;

	return (&root);
}

t_gcnode	*create_n(void *ptr)
{
	t_gcnode	*node;

	node = malloc(sizeof(t_gcnode));
	if (!node)
		return (NULL);
	node->address = ptr;
	node->next = NULL;
	return (node);
}

void	append_node(t_gcnode **head, t_gcnode *new_node)
{
	t_gcnode	*current;

	if (!head || !new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	*nalloc(size_t __size)
{
	void		*ptr;
	t_gcnode	*node;
	t_gcnode	**tracker;

	tracker = memory_tracker();
	ptr = malloc(__size);
	if (!ptr)
	{
		free_all_tracked();
		exit(EXIT_FAILURE);
	}
	node = create_n(ptr);
	if (!node)
	{
		free(ptr);
		free_all_tracked();
		exit(EXIT_FAILURE);
	}
	append_node(tracker, node);
	return (ptr);
}

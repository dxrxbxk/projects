/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:51:32 by momadani          #+#    #+#             */
/*   Updated: 2022/11/16 20:39:07 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_child_add_back(t_child **child, t_child *elem)
{
	t_child	*current;

	current = *child;
	if (!*child)
		*child = elem;
	else
	{
		while (current->next)
			current = current->next;
		current->next = elem;
		elem->prev = current;
	}
}

t_child	*ft_child_new(void)
{
	t_child	*new;

	new = malloc(sizeof(t_child));
	if (!new)
		return (NULL);
	new->pathname = NULL;
	new->argv = NULL;
	new->envp = NULL;
	new->redir = NULL;
	new->status = 0;
	new->pid = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

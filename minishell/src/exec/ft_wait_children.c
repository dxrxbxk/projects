/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_children.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:39:00 by momadani          #+#    #+#             */
/*   Updated: 2022/11/19 18:00:22 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_child	*ft_getchild(t_child *child, pid_t pid)
{
	while (child && child->pid != pid)
		child = child->next;
	return (child);
}

int	ft_wait_children(t_child *first)
{
	t_child		*child;
	pid_t		pid;
	int			status;

	pid = waitpid(-1, &status, 0);
	if (pid == -1)
		return (1);
	child = ft_getchild(first, pid);
	if (!child)
		return (0);
	child->status = status;
	return (ft_wait_children(first));
}

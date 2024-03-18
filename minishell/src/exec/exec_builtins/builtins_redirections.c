/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:38:03 by momadani          #+#    #+#             */
/*   Updated: 2022/11/20 18:57:35 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_save_main_fds(int fds[2], t_child *child)
{
	if (!child->redir)
		return (0);
	fds[0] = dup(0);
	if (fds[0] == -1)
		return (set_child_status(child,
				ft_error("dup: ", strerror(errno), NULL, 1)));
	fds[1] = dup(1);
	if (fds[1] == -1)
		return (set_child_status(child,
				ft_error("dup: ", strerror(errno), NULL, 1)));
	return (0);
}

int	ft_restore_main_fds(int fds[2], t_child *child)
{
	if (!child->redir)
		return (0);
	if (dup2(fds[0], 0) == -1)
		return (set_child_status(child,
				ft_error("dup2: ", strerror(errno), NULL, 1)));
	if (close(fds[0]) == -1)
		return (set_child_status(child,
				ft_error("close: ", strerror(errno), NULL, 1)));
	if (dup2(fds[1], 1) == -1)
		return (set_child_status(child,
				ft_error("dup2: ", strerror(errno), NULL, 1)));
	if (close(fds[1]) == -1)
		return (set_child_status(child,
				ft_error("close: ", strerror(errno), NULL, 1)));
	return (0);
}

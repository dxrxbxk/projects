/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interpret_child_status.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 18:03:48 by momadani          #+#    #+#             */
/*   Updated: 2022/11/20 23:54:24 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_is_sigint(int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (1);
	return (0);
}

int	ft_is_sigquit(int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		return (1);
	return (0);
}

int	ft_apply_signal_msg(int is_sigint, int status)
{
	if (is_sigint == 130)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (ft_is_sigquit(status))
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	return (0);
}

int	ft_get_exit_status(int status)
{
	int	exit_status;

	exit_status = 0;
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		exit_status = 130;
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		exit_status = 131;
	else if (WIFEXITED(status))
		exit_status = (WEXITSTATUS(status));
	else
		exit_status = status;
	return (exit_status);
}

int	ft_interpret_child_status(t_child *child)
{
	int	exit_status;
	int	tmp;

	if (!child)
		return (1);
	tmp = 0;
	exit_status = 0;
	while (child)
	{
		if (ft_is_sigint(child->status))
			tmp |= 130;
		if (!child->next)
			break ;
		child = child->next;
	}
	ft_apply_signal_msg(tmp, child->status);
	exit_status = ft_get_exit_status(child->status);
	g_status = exit_status;
	return (tmp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipe_fds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 03:16:33 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 16:08:55 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_get_pipein_redir_rank(t_redir *redir)
{
	int	rank;

	rank = 0;
	while (redir[rank].type != PIPE_IN && redir[rank].type != END)
		rank++;
	if (redir[rank].type == PIPE_IN)
		return (rank);
	return (0);
}

int	ft_get_pipeout_redir_rank(t_redir *redir)
{
	int	rank;

	rank = 0;
	while (redir[rank].type != PIPE_OUT && redir[rank].type != END)
		rank++;
	if (redir[rank].type == PIPE_OUT)
		return (rank);
	return (0);
}

int	ft_create_pipe(t_child *child)
{
	int	pipefd[2];
	int	pipeout_rank;
	int	pipein_rank;

	if (!child->next)
		return (0);
	if (pipe(pipefd) == -1)
		return (ft_error("pipe: ", strerror(errno), NULL, -1));
	pipeout_rank = ft_get_pipeout_redir_rank(child->redir);
	pipein_rank = ft_get_pipein_redir_rank(child->next->redir);
	if (child->redir[pipeout_rank].type == PIPE_OUT)
		child->redir[pipeout_rank].fd = pipefd[1];
	if (child->next->redir[pipein_rank].type == PIPE_IN)
		child->next->redir[pipein_rank].fd = pipefd[0];
	return (1);
}

int	ft_close_pipe(t_child *child)
{
	int	pipeout_rank;
	int	pipein_rank;
	int	pipeout_fd;
	int	pipein_fd;

	if (!child->prev)
		return (0);
	pipeout_rank = ft_get_pipeout_redir_rank(child->prev->redir);
	pipein_rank = ft_get_pipein_redir_rank(child->redir);
	pipein_fd = -1;
	pipeout_fd = -1;
	if (child->prev->redir[pipeout_rank].type == PIPE_OUT)
		pipeout_fd = child->prev->redir[pipeout_rank].fd;
	if (child->redir[pipein_rank].type == PIPE_IN)
		pipein_fd = child->redir[pipein_rank].fd;
	if (close(pipeout_fd) == -1)
		return (ft_error("close: ", strerror(errno), NULL, -1));
	if (close(pipein_fd) == -1)
		return (ft_error("close: ", strerror(errno), NULL, -1));
	return (1);
}

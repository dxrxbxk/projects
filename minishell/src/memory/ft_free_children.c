/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_children.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 19:02:41 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 03:37:49 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_child	*ft_get_first_child(t_child *child)
{
	while (child && child->prev)
		child = child->prev;
	return (child);
}

void	free_redir_struct(t_redir *redir)
{
	t_redir	*tmp;

	if (!redir)
		return ;
	tmp = redir;
	while (redir->type != END)
	{
		if (redir->path)
			free(redir->path);
		ft_close(&redir->fd);
		redir++;
	}
	free(tmp);
}

void	ft_delchild(t_child *child)
{
	free(child->pathname);
	free_tab(&child->argv);
	free_tab(&child->envp);
	free_redir_struct(child->redir);
	child->pathname = NULL;
	child->redir = NULL;
	free(child);
}

void	ft_free_child(t_child *child)
{
	if (child->next)
		ft_free_child(child->next);
	ft_delchild(child);
}

int	ft_free_children(t_child *child)
{
	if (!child)
		return (1);
	child = ft_get_first_child(child);
	if (!child)
		return (1);
	ft_free_child(child);
	return (0);
}

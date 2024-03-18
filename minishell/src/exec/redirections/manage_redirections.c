/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 05:18:33 by momadani          #+#    #+#             */
/*   Updated: 2022/11/20 19:46:17 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_add_cmd_redirections(t_redir *redir, t_ast *ast)
{
	t_redir_type	type;
	char			*path;
	int				fd;

	while (ast && ast->left)
	{
		type = ft_which_redir(ast->token->type);
		path = ft_strdup(ast->left->token->str);
		if (!path && ast->left->token->str != NULL)
			return (ft_error(MEM_ERROR, NULL, NULL, -1));
		fd = -1;
		ft_fill_redir_struct(redir, type, path, fd);
		ast = ast->left;
		if (ast)
			ast = ast->left;
		redir++;
	}
	ft_fill_redir_struct(redir, END, NULL, -1);
	return (0);
}

int	ft_apply_redirections(t_redir *redir, t_child *child)
{
	if (!redir)
		return (0);
	while (redir->type != END)
	{
		if (!redir->path && redir->type != PIPE_IN && redir->type != PIPE_OUT)
			return (set_child_status(child,
					ft_error("ambiguous redirect", NULL, NULL, 1)));
		if (redir->type != PIPE_IN && redir->type != PIPE_OUT)
			redir->fd = ft_open(redir->path, redir->type);
		if (redir->fd == -1)
			return (set_child_status(child,
					ft_error(redir->path, ": ", strerror(errno), 1)));
		if (ft_dup2(redir->fd, redir->type) == -1)
			return (set_child_status(child,
					ft_error(redir->path, ": ", strerror(errno), 1)));
		if (ft_close(&redir->fd) == -1)
			return (set_child_status(child,
					ft_error(redir->path, ": ", strerror(errno), 1)));
		redir++;
	}
	return (0);
}

int	ft_get_cmd_redirections(t_child *child, t_ast *ast)
{
	if (!ast)
		return (0);
	child->redir = malloc(sizeof(t_redir) * ((ft_lbranch_len(ast) / 2) + 1));
	if (!child->redir)
		return (set_child_status(child, ft_error(MEM_ERROR, NULL, NULL, 1)));
	if (ft_add_cmd_redirections(child->redir, ast) == -1)
		return (set_child_status(child, 1));
	return (0);
}

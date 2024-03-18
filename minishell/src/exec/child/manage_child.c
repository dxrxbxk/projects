/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 03:08:12 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 12:09:41 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	launch_child(t_ast *ast, t_mini *data)
{
	t_child	*child;
	int		end_status;

	child = ft_child_new();
	if (!child)
		return (ft_error(MEM_ERROR, NULL, NULL, -1));
	ft_memptr_child(&child);
	if (is_builtin(ast->right))
		return (launch_builtin(child, ast, data));
	child->pid = fork();
	if (child->pid == -1)
		return (ft_free_children(child), ft_error("fork: ",
				strerror(errno), NULL, -1));
	if (child->pid == 0)
		exec_child(child, ast, data);
	ft_wait_children(child);
	end_status = ft_interpret_child_status(child);
	ft_free_children(child);
	if (end_status == 130)
		return (-1);
	return (0);
}

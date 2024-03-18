/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:45:35 by momadani          #+#    #+#             */
/*   Updated: 2022/11/20 20:27:55 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_child(t_child *child, t_ast *ast, t_mini *data)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (ft_get_cmd_redirections(child, ast->left) != 0)
		ft_exit_free(data, child, child->status);
	if (ft_apply_redirections(child->redir, child) != 0)
		ft_exit_free(data, child, child->status);
	if (ft_get_args(child, ast->right) != 0)
		ft_exit_free(data, child, child->status);
	if (!child->argv || !*child->argv)
		ft_exit_free(data, child, 0);
	ft_find_cmd_path(child, data);
	ft_check_is_directory(data, child, child->pathname);
	child->envp = ft_lst_to_tab(data->env);
	execve(child->pathname, child->argv, child->envp);
	ft_error("execve: ", strerror(errno), NULL, 1);
	ft_exit_free(data, child, 1);
}

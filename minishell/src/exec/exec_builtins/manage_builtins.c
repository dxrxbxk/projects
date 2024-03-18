/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:33:24 by momadani          #+#    #+#             */
/*   Updated: 2022/11/23 02:47:14 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_quit_free_builtin(t_child *child)
{
	g_status = child->status;
	ft_free_children(child);
	return (0);
}

t_built	*init_fpointer(void)
{
	static t_built	data[NB_BUILTS];

	data[0].builtins = &ft_echo;
	data[0].cmd = "echo";
	data[1].builtins = &ft_env;
	data[1].cmd = "env";
	data[2].builtins = &ft_pwd;
	data[2].cmd = "pwd";
	data[3].builtins = &ft_cd;
	data[3].cmd = "cd";
	data[4].builtins = &ft_exit;
	data[4].cmd = "exit";
	data[5].builtins = &ft_export;
	data[5].cmd = "export";
	data[6].builtins = &ft_unset;
	data[6].cmd = "unset";
	return (data);
}

int	is_builtin(t_ast *ast)
{
	t_built	*data;
	char	*cmd;
	int		i;

	cmd = NULL;
	while (ast && !ast->token->str)
		ast = ast->right;
	if (ast)
		cmd = ast->token->str;
	if (!ast || !cmd)
		return (0);
	data = init_fpointer();
	i = -1;
	while (++i < NB_BUILTS)
	{
		if (!ft_strcmp(data[i].cmd, cmd))
			return (1);
		else if (!ft_strcmp("unset", cmd))
			return (1);
	}
	return (0);
}

int	launch_builtin(t_child *child, t_ast *ast, t_mini *data)
{
	int	main_fds[2];

	if (ft_get_cmd_redirections(child, ast->left) != 0)
		return (ft_quit_free_builtin(child));
	if (ft_save_main_fds(main_fds, child) != 0)
		return (ft_quit_free_builtin(child));
	if (ft_apply_redirections(child->redir, child) != 0)
	{
		ft_restore_main_fds(main_fds, child);
		return (ft_quit_free_builtin(child));
	}
	g_status = exec_builtin(child, ast, data);
	if (ft_restore_main_fds(main_fds, child) != 0)
		return (ft_quit_free_builtin(child));
	ft_free_children(child);
	return (0);
}

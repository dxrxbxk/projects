/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 03:22:44 by momadani          #+#    #+#             */
/*   Updated: 2022/12/08 20:50:05 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	set_child_status(t_child *child, int exit_status)
{
	child->status = exit_status;
	return (exit_status);
}

void	ft_exit_free(t_mini *data, t_child *child, int retval)
{
	ft_free_children(child);
	ft_free_ast_child(data->root);
	ft_free_data(data);
	exit(retval);
}

int	ft_get_args(t_child *child, t_ast *ast)
{
	size_t	i;

	if (!ast)
		return (0);
	child->argv = malloc(sizeof(char *) * (ft_rbranch_len_skip_null(ast) + 1));
	if (!child->argv)
		return (set_child_status(child, ft_error(MEM_ERROR, NULL, NULL, 1)));
	i = 0;
	while (ast)
	{
		if (ast->token->str)
		{
			child->argv[i] = ft_strdup(ast->token->str);
			if (!child->argv)
				return (set_child_status(child,
						ft_error(MEM_ERROR, NULL, NULL, 1)));
			i++;
		}
		ast = ast->right;
	}
	child->argv[i] = NULL;
	return (0);
}

int	ft_check_is_directory(t_mini *data, t_child *child, char *path)
{
	struct stat	sb;

	if (lstat(path, &sb) == -1)
		ft_exit_free(data, child, ft_error("lstat", NULL, NULL, 1));
	if (sb.st_mode & S_IFDIR)
		ft_exit_free(data, child, ft_error(path,
				": Is a directory", NULL, 126));
	return (0);
}

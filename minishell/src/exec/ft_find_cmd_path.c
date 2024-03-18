/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 00:01:22 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 16:25:13 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_strrealloc_pathname(t_child *child, t_mini *data,
									char *cmd, char *prefix)
{
	char	*dest;

	dest = ft_mega_join(prefix, "/", cmd);
	if (!dest)
		ft_exit_free(data, child, ft_error(MEM_ERROR, NULL, NULL, 1));
	free(child->pathname);
	child->pathname = dest;
	return (1);
}

static int	ft_try_path(t_child *child, t_mini *data, char **spath)
{
	if (!spath || !*spath)
		return (0);
	ft_strrealloc_pathname(child, data, child->argv[0], *spath);
	if (!access(child->pathname, F_OK | X_OK))
		return (1);
	return (ft_try_path(child, data, spath + 1));
}

static int	ft_check_absolute_relative_path(t_mini *data, t_child *child)
{
	if (!access(child->pathname, F_OK | X_OK))
		return (1);
	ft_error(child->pathname, ": ", strerror(errno), 1);
	ft_exit_free(data, child, 127);
	return (0);
}

int	ft_find_cmd_path(t_child *child, t_mini *data)
{
	char	*cmd;

	cmd = child->argv[0];
	child->pathname = ft_strdup(cmd);
	if (!child->pathname)
		ft_exit_free(data, child, ft_error(MEM_ERROR, NULL, NULL, 1));
	if (ft_strchr(cmd, '.') || ft_strchr(cmd, '/')
		|| !data->spath || !*data->spath)
		ft_check_absolute_relative_path(data, child);
	else if (!*child->pathname || !ft_try_path(child, data, data->spath))
		ft_exit_free(data, child,
			ft_error(child->argv[0], ": command not found", NULL, 127));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 23:49:51 by momadani          #+#    #+#             */
/*   Updated: 2022/11/20 19:47:09 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_open(char *path, t_redir_type type)
{
	int		fd;
	int		flags;
	mode_t	mode;

	mode = 0;
	flags = 0;
	if (type == INFILE || type == HEREDOC)
		flags = O_RDONLY;
	else if (type == OUTFILE)
	{
		flags = O_WRONLY | O_CREAT | O_TRUNC;
		mode = 0666;
	}
	else if (type == APPEND)
	{
		flags = O_WRONLY | O_CREAT | O_APPEND;
		mode = 0666;
	}
	fd = open(path, flags, mode);
	return (fd);
}

int	ft_dup2(int fd, t_redir_type type)
{
	int	retval;

	retval = 0;
	if (type == INFILE || type == HEREDOC || type == PIPE_IN)
		retval = dup2(fd, STDIN_FILENO);
	else if (type == OUTFILE || type == APPEND || type == PIPE_OUT)
		retval = dup2(fd, STDOUT_FILENO);
	return (retval);
}

int	ft_close(int *fd)
{
	int	ret;

	if (*fd == -1)
		return (1);
	ret = close(*fd);
	*fd = -1;
	return (ret);
}

t_redir_type	ft_which_redir(t_type type)
{
	if (type == LESS)
		return (INFILE);
	else if (type == D_LESS)
		return (HEREDOC);
	else if (type == GREAT)
		return (OUTFILE);
	else if (type == D_GREAT)
		return (APPEND);
	return (END);
}

void	ft_fill_redir_struct(t_redir *redir,
			t_redir_type type, char *path, int fd)
{
	redir->type = type;
	redir->path = path;
	redir->fd = fd;
}

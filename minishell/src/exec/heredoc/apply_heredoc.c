/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 18:14:47 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/21 13:28:34 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define HERE_DOC_WARNING "warning: here-document at line "
#define HERE_DOC_EOF " delimited by end-of-file (wanted `"

char	*heredoc_path(void)
{
	static int	i = 1;
	char		*path;
	char		*nb;

	nb = ft_itoa(i);
	path = ft_mega_join("/tmp/", "minishell_tmp_", nb);
	i++;
	free(nb);
	return (path);
}

static int	null_line(int *i, char *delim)
{
	char	*arg;
	char	*arg2;

	arg = ft_itoa(*i);
	arg2 = ft_mega_join(HERE_DOC_EOF, delim, "\')");
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_error(HERE_DOC_WARNING, arg, arg2, -1);
	free(arg);
	free(arg2);
	return (*i = 0);
}

static int	check_len(char *s1, char *s2)
{
	if (ft_strlen(s1) == ft_strlen(s2) - 1)
		return (0);
	return (1);
}

static int	get_and_write(int fd, char *delim)
{
	char		*line;
	static int	i = 0;

	ft_putstr_fd("> ", 1);
	line = get_next_line(0);
	if (line && ft_strcmp(line, "\n"))
		i++;
	if (!line)
		return (null_line(&i, delim));
	else if (!ft_strncmp(delim, line, ft_strlen(delim))
		&& !check_len(delim, line))
		return (free(line), i = 0);
	else
		write(fd, line, ft_strlen(line));
	free(line);
	return (1);
}

int	apply_heredoc(char *path, char *delim)
{
	int	fd;

	if (!delim)
		return (1);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (ft_error("open: ", strerror(errno), NULL, 1));
	while (get_and_write(fd, delim))
		;
	if (close(fd) == -1)
		return (ft_error("close: ", strerror(errno), NULL, 1));
	return (0);
}

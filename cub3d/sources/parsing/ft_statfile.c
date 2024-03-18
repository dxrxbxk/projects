/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_statfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:31:14 by momadani          #+#    #+#             */
/*   Updated: 2023/02/23 00:39:49 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	ft_check_cub_ext(char *pathname)
{
	char	*ext;

	ext = ft_strrchr(pathname, '.');
	if (!ext)
		return (0);
	return (!ft_strcmp(ext, ".cub"));
}

int	ft_statfile(char *filepath)
{
	int	fd;

	if (!ft_check_cub_ext(filepath))
		ft_exit_error(filepath, ": expected .cub file extension", NULL, 2);
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		ft_exit_error(filepath, ": ", strerror(errno), 2);
	return (fd);
}

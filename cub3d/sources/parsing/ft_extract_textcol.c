/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_textcol.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:23:13 by momadani          #+#    #+#             */
/*   Updated: 2023/03/16 00:21:25 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	ft_skip_whitespaces(char **s)
{
	while (**s && ft_strchr(WHITE_SPACES, **s))
		(*s)++;
}

int	is_color_type(char *s)
{
	ft_skip_whitespaces(&s);
	if (*s && ft_strchr(WHITE_SPACES, *(s + 1)))
		return (1);
	return (0);
}

int	ft_getrank(char *type, size_t *rank)
{
	if (!ft_strcmp(type, "NO"))
		*rank = NORTH;
	else if (!ft_strcmp(type, "SO"))
		*rank = SOUTH;
	else if (!ft_strcmp(type, "WE"))
		*rank = WEST;
	else if (!ft_strcmp(type, "EA"))
		*rank = EAST;
	else
		return (0);
	return (1);
}

int	ft_extract_textcol(t_game *game, char *line,
								char *textures_paths[NB_TEXTURES], int fd)
{
	char	**assets_info;
	size_t	rank;

	rank = 0;
	if (is_color_type(line))
		return (get_color(line, game->colors, textures_paths, fd));
	assets_info = ft_split(line, " \t\n");
	free(line);
	if (!assets_info)
		(close(fd), free_text_path(textures_paths),
			ft_exit_error("malloc: ", strerror(errno), NULL, 5));
	else if (ft_strs_len(assets_info) != 2)
		(close(fd), ft_free_strs(assets_info), free_text_path(textures_paths),
			ft_exit_error("expected <type identifier> <path>", NULL, NULL, 2));
	else if (!ft_getrank(assets_info[0], &rank))
		(close(fd), ft_free_strs(assets_info), free_text_path(textures_paths),
			ft_exit_error(NULL, "unknown type identifier", NULL, 2));
	if (textures_paths[rank] == NULL)
		textures_paths[rank] = ft_strdup(assets_info[1]);
	else
		(close(fd), ft_free_strs(assets_info), free_text_path(textures_paths),
			ft_exit_error(NULL, "multiple definition of a texture", NULL, 2));
	ft_free_strs(assets_info);
	return (0);
}

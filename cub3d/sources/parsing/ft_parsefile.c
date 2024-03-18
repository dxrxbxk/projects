/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsefile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:04:01 by momadani          #+#    #+#             */
/*   Updated: 2023/03/16 00:20:43 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	ft_isempty_line(char *line)
{
	while (line && ft_strchr(WHITE_SPACES, *line))
		line++;
	return (line && *line == '\n' && *(line + 1) == '\0');
}

int	get_next_nonempty_line(int fd, char **line)
{
	*line = get_next_line(fd);
	while (*line && ft_isempty_line(*line))
	{
		free(*line);
		*line = get_next_line(fd);
	}
	return (*line != NULL);
}

char	**ft_strsrealloc(char **src, char *s)
{
	char	**dest;
	size_t	i;

	dest = malloc(sizeof(char *) * (ft_strs_len(src) + 2));
	if (!dest)
		ft_exit_error("malloc: ", strerror(errno), NULL, 1);
	i = 0;
	while (src && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i++] = s;
	dest[i] = NULL;
	free(src);
	return (dest);
}

int	ft_parsefile(t_game *game, int fd, char *textures_paths[NB_TEXTURES])
{
	static char	*line = NULL;
	int			i;

	i = -1;
	while (++i < NB_TEXTURES + 2)
	{
		if (!get_next_nonempty_line(fd, &line))
			(close(fd), free_text_path(textures_paths),
				ft_exit_error("textures or colors missing", NULL, NULL, 3));
		ft_extract_textcol(game, line, textures_paths, fd);
	}
	if (!get_next_nonempty_line(fd, &line))
		(close(fd), free(line), free_text_path(textures_paths),
			ft_exit_error("no scene found", NULL, NULL, 3));
	while (line && !ft_isempty_line(line))
	{
		game->map.map = ft_strsrealloc(game->map.map, line);
		line = get_next_line(fd);
	}
	if (line)
		(free(line), get_next_nonempty_line(fd, &line));
	if (line)
		(close(fd), free(line), free_text_path(textures_paths),
			ft_exit_error("scene followed by lines", NULL, NULL, 3));
	return (0);
}

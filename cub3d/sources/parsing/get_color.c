/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:23:13 by momadani          #+#    #+#             */
/*   Updated: 2023/03/20 17:19:47 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	ft_atoc(char **s)
{
	int	rgb_value;

	rgb_value = 0;
	if (!s || !(**s >= '0' && **s <= '9'))
		return (-1);
	while (**s && **s >= '0' && **s <= '9')
	{
		rgb_value = (rgb_value * 10) + (**s - 48);
		if (rgb_value > UCHAR_MAX)
			return (-2);
		(*s)++;
	}
	ft_skip_whitespaces(s);
	if (**s != ',' && **s != '\n' && **s != '\0')
		return (-3);
	return (rgb_value);
}

uint32_t	rgb_to_int(int rgb[3])
{
	uint32_t	color;

	color = 0;
	color |= (rgb[0] << 16) & 0x00ff0000;
	color |= (rgb[1] << 8) & 0x0000ff00;
	color |= (rgb[2] << 0) & 0x000000ff;
	return (color);
}

char	*get_rgb(char *line, int rgb[3], char *path[NB_TEXTURES], int fd)
{
	char	*pos;
	int		i;

	pos = line;
	ft_skip_whitespaces(&pos);
	pos++;
	i = 0;
	while (i < 3)
	{
		ft_skip_whitespaces(&pos);
		rgb[i] = ft_atoc(&pos);
		if (rgb[i] == -1 || rgb[i] == -3 || (!pos && i != 2))
			(close(fd), free(line), free_text_path(path),
				ft_exit_error(\
		"expected <type identifier> <[0-255],[0-255],[0-255]>", NULL, NULL, 2));
		if (rgb[i] == -2)
			(close(fd), free(line), free_text_path(path),
				ft_exit_error("RGB value out of range", NULL, NULL, 2));
		if (i != 2)
			pos = ft_strchr(pos, ',');
		if (pos && i != 2)
			pos++;
		i++;
	}
	return (pos);
}

int	get_color(char *line, uint32_t colors[2], char *path[NB_TEXTURES], int fd)
{
	size_t	rank;
	int		rgb[3];
	char	*pos;

	rank = 0;
	pos = line;
	ft_skip_whitespaces(&pos);
	if (!ft_strncmp(pos, "C", 1))
		rank = CEIL;
	else if (!ft_strncmp(pos, "F", 1))
		rank = FLOOR;
	else
		(close(fd), free(line), free_text_path(path),
			ft_exit_error("unknown type identifier", NULL, NULL, 2));
	pos = get_rgb(line, rgb, path, fd);
	if (!(colors[rank] >> 31 & 1))
		(close(fd), free(line), free_text_path(path),
			ft_exit_error("multiple definition of a color", NULL, NULL, 2));
	colors[rank] = rgb_to_int(rgb);
	ft_skip_whitespaces(&pos);
	if (*pos && *pos != '\n' && *(pos + 1) != '\0')
		(close(fd), free(line), free_text_path(path), ft_exit_error(\
		"expected <type identifier> <[0-255],[0-255],[0-255]>", NULL, NULL, 2));
	free(line);
	return (0);
}

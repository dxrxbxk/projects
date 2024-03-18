/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsemap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:37:58 by momadani          #+#    #+#             */
/*   Updated: 2023/03/20 03:36:04 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

double	init_angle(char direction)
{
	if (direction == 'S')
		return (M_PI / 2);
	else if (direction == 'N')
		return ((3 * M_PI) / 2);
	else if (direction == 'E')
		return (2 * M_PI);
	else if (direction == 'W')
		return (M_PI);
	return (-1);
}

static int	ft_parsetile(char **map, t_player *player, int i, int j)
{
	char	tile;

	tile = map[i][j];
	if (!ft_strchr(VALID_ELEM, tile))
		return (1);
	if (ft_strchr(INSIDE_ELEM, tile) && !ft_check_inside_surrounding(map, j, i))
		return (2);
	if (ft_strchr(OUTSIDE_ELEM, tile)
		&& !ft_check_outside_surrounding(map, j, i))
		return (2);
	if (ft_strchr(PLAYER_ELEM, tile) && (player->x || player->y))
		return (3);
	if (ft_strchr(PLAYER_ELEM, tile) && !player->x && !player->y)
	{
		player->x = (j * CELL_SIZE) + CELL_SIZE / 2;
		player->y = (i * CELL_SIZE) + CELL_SIZE / 2;
		player->angle = init_angle(tile);
		player->dir_x = cos(player->angle) * 5;
		player->dir_y = sin(player->angle) * 5;
	}
	return (0);
}

static void	ft_maperror(int ret, char *textures_paths[NB_TEXTURES])
{
	free_text_path(textures_paths);
	if (ret == 1)
		ft_exit_error("invalid element found", NULL, NULL, 3);
	else if (ret == 2)
		ft_exit_error("map not surrounded by walls", NULL, NULL, 3);
	else if (ret == 3)
		ft_exit_error("multiple player definition", NULL, NULL, 3);
}

int	ft_parsemap(t_map *map, t_player *player, char *textures_paths[NB_TEXTURES])
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j] != '\n' && map->map[i][j])
		{
			ret = ft_parsetile(map->map, player, i, j);
			if (ret)
				ft_maperror(ret, textures_paths);
			j++;
		}
		if (j > map->width)
			map->width = j;
		i++;
	}
	if (!player->x && !player->y)
		(free_text_path(textures_paths),
			ft_exit_error("no player definition", NULL, NULL, 3));
	map->height = i;
	return (0);
}

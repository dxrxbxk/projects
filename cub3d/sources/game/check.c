/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 00:43:04 by momadani          #+#    #+#             */
/*   Updated: 2023/03/20 02:42:45 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

bool	is_valid_move(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || y >= map->height || x >= ft_strlen(map->map[y]))
		return (false);
	if (ft_strchr(CLOSING_ELEM, map->map[y][x]))
		return (false);
	return (true);
}

bool	is_within_bounds(t_map *map, int x, int y)
{
	return (x >= 0 && y >= 0 && y < map->height && x < ft_strlen(map->map[y]));
}

bool	is_adjacent(t_map *map, int x, int y)
{
	int	dx;
	int	dy;

	dx = x / CELL_SIZE;
	dy = y / CELL_SIZE;
	if (dx > 0 && !is_valid_move(map, (x - 1) / CELL_SIZE, dy)
		&& dy > 0 && !is_valid_move(map, dx, (y - 1) / CELL_SIZE))
		return (true);
	if (dy > 0 && !is_valid_move(map, dx, (y - 1) / CELL_SIZE)
		&& dx < ft_strlen(map->map[dy])
		&& !is_valid_move(map, (x + 1) / CELL_SIZE, dy))
		return (true);
	if (dy > 0 && dy < map->height
		&& !is_valid_move(map, dx, (y + 1) / CELL_SIZE)
		&& dx > 0 && !is_valid_move(map, (x - 1) / CELL_SIZE, dy))
		return (true);
	if (dy > 0 && dy < map->height
		&& !is_valid_move(map, dx, (y + 1) / CELL_SIZE)
		&& dx < ft_strlen(map->map[dy])
		&& !is_valid_move(map, (x + 1) / CELL_SIZE, dy))
		return (true);
	return (false);
}

bool	is_wall(t_map *map, int x, int y)
{
	if (ft_strchr(CLOSING_ELEM, map->map[y][x]))
		return (true);
	return (false);
}

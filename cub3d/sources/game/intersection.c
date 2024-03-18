/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 01:34:45 by momadani          #+#    #+#             */
/*   Updated: 2023/03/20 16:14:36 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

double	find_vertical(double px, double py, double ra, t_game *game)
{
	t_inter	*v;
	double	tan_v;

	v = &game->data[V];
	tan_v = tan((ra));
	v->hit = false;
	if (cos((ra)) > 0.001)
	{
		v->rx = (((int)px >> 6) << 6) + CELL_SIZE;
		v->ry = (px - v->rx) * tan_v + py;
		v->xo = CELL_SIZE;
		v->yo = -v->xo * tan_v;
		v->hit = EAST;
	}
	else if (cos((ra)) < -0.001)
	{
		v->rx = (((int)px >> 6) << 6) - 0.0001;
		v->ry = (px - v->rx) * tan_v + py;
		v->xo = -CELL_SIZE;
		v->yo = -v->xo * tan_v;
		v->hit = WEST;
	}
	else
		return (MAX_DIST);
	return (find_next_intersection(game, ra, v));
}

double	find_horizontal(double px, double py, double ra, t_game *game)
{
	t_inter			*h;
	double			tan_h;

	h = &game->data[H];
	tan_h = 1.0 / tan((ra));
	h->hit = false;
	if (sin((ra)) > 0.001)
	{
		h->ry = (((int)py >> 6) << 6) - 0.0001;
		h->rx = (py - h->ry) * tan_h + px;
		h->yo = -CELL_SIZE;
		h->xo = -h->yo * tan_h;
		h->hit = NORTH;
	}
	else if (sin((ra)) < -0.001)
	{
		h->ry = (((int)py >> 6) << 6) + CELL_SIZE;
		h->rx = (py - h->ry) * tan_h + px;
		h->yo = CELL_SIZE;
		h->xo = -h->yo * tan_h;
		h->hit = SOUTH;
	}
	else
		return (MAX_DIST);
	return (find_next_intersection(game, ra, h));
}

double	find_next_intersection(t_game *game, double ra, t_inter *data)
{
	int		dof;
	double	dist;
	t_map	*map;

	dist = MAX_DIST;
	map = &game->map;
	dof = -1;
	while (++dof < MAX_DOF)
	{
		if (is_within_bounds(map, data->rx / CELL_SIZE, data->ry / CELL_SIZE)
			&& (is_wall(map, data->rx / CELL_SIZE, data->ry / CELL_SIZE)
				|| is_adjacent(map, data->rx, data->ry)))
		{
			dist = cos(ra) * (data->rx - game->player.x)
				- sin(ra) * (data->ry - game->player.y);
			break ;
		}
		else
		{
			data->rx += data->xo;
			data->ry += data->yo;
		}
	}
	return (dist);
}

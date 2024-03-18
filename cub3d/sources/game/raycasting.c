/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 01:38:36 by momadani          #+#    #+#             */
/*   Updated: 2023/03/20 02:43:16 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	color_range_checker(int color)
{
	if (color < 0)
		return (0);
	else if (color > 255)
		return (255);
	return (color);
}

int	color_multiplier(int color, float multiplier)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (int)(r * multiplier);
	g = (int)(g * multiplier);
	b = (int)(b * multiplier);
	r = color_range_checker(r);
	g = color_range_checker(g);
	b = color_range_checker(b);
	return ((r << 16) | (g << 8) | b);
}

void	init_display(t_display *d,
								t_game *game, double ray_angle, double distance)
{
	double	angle_diff;
	double	corrected_distance;
	t_img	*texture;

	if (game->is_horizontal == true)
		texture = game->textures[game->data[H].hit];
	else
		texture = game->textures[game->data[V].hit];
	angle_diff = ray_angle - game->player.angle;
	corrected_distance = distance * cos(angle_diff);
	d->wall_height = (WALL_HEIGHT / corrected_distance) * DIST_PROJ_PLANE;
	d->wall_top = (WINDOW_HEIGHT - d->wall_height) / 2;
	d->wall_bottom = d->wall_top + d->wall_height - 1;
	if (game->is_horizontal == true)
		d->tex_x = fmod(game->data[H].rx, CELL_SIZE)
			* (texture->width / CELL_SIZE);
	else
		d->tex_x = fmod(game->data[V].ry, CELL_SIZE)
			* (texture->width / CELL_SIZE);
}

void	draw_ray(t_game *game, int x, double ray_angle, double distance)
{
	t_img		*texture;
	t_display	d;
	int			y;

	init_display(&d, game, ray_angle, distance);
	if (game->is_horizontal == true)
		texture = game->textures[game->data[H].hit];
	else
		texture = game->textures[game->data[V].hit];
	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		if (y < d.wall_top)
			ft_mlx_pixel_put_image(game->mlx_img, game->colors[CEIL], x, y);
		else if (y > d.wall_bottom)
			ft_mlx_pixel_put_image(game->mlx_img, color_multiplier(\
		game->colors[FLOOR], 1.0 - ((WINDOW_HEIGHT - y) / 50.0 * 0.1)), x, y);
		else
		{
			d.tex_y = ((y - d.wall_top) * texture->height) / d.wall_height;
			d.color = mlx_get_pixel_color(texture, abs(d.tex_x), abs(d.tex_y));
			d.color = color_multiplier(d.color, 1.0 - (distance / 80.0 * 0.1));
			ft_mlx_pixel_put_image(game->mlx_img, d.color, x, y);
		}
	}
}

void	draw_game(t_game *game)
{
	double	dis_v;
	double	dis_h;
	double	ray_angle;
	double	x;

	x = -WINDOW_WIDTH / 2 - 1;
	while (++x < WINDOW_WIDTH / 2)
	{
		ray_angle = (game->player.angle + (x / WINDOW_WIDTH)
				* (FOV * M_PI / 180)) * -1;
		dis_h = find_horizontal(game->player.x,
				game->player.y, ray_angle, game);
		dis_v = find_vertical(game->player.x, game->player.y, ray_angle, game);
		if (dis_h > dis_v)
		{
			game->is_horizontal = false;
			draw_ray(game, x + (WINDOW_WIDTH >> 1), -ray_angle, dis_v);
		}
		else
		{
			game->is_horizontal = true;
			draw_ray(game, x + (WINDOW_WIDTH >> 1), -ray_angle, dis_h);
		}
	}
}

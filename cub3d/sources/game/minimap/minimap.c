/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 02:48:35 by momadani          #+#    #+#             */
/*   Updated: 2023/03/20 03:22:11 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	draw_outside_circle(t_game *game, int i, int j)
{
	t_pos	d;

	d.x = j - MMAP_SIZE;
	d.y = i - MMAP_SIZE;
	if (sqrt(d.x * d.x + d.y * d.y) > MMAP_SIZE - 3
		&& sqrt(d.x * d.x + d.y * d.y) < MMAP_SIZE + 1)
		ft_mlx_pixel_put_image(game->mlx_img, MMAP_CIRCLE_COLOR,
			j + MMAP_OFFSET, i + MMAP_OFFSET);
	if (sqrt(d.x * d.x + d.y * d.y) > MMAP_SIZE - 3)
		return (1);
	return (0);
}

static void	draw_circle(t_game *game, int i, int j, t_pos p)
{
	char	pixel;
	char	**map;

	if (draw_outside_circle(game, i, j))
		return ;
	map = game->map.map;
	if (p.x < 0 || p.y < 0 || !map[(int)(p.y / MINIMAP_CELL_SIZE)]
		|| !map[(int)(p.y / MINIMAP_CELL_SIZE)][(int)(p.x / MINIMAP_CELL_SIZE)])
	{
		ft_mlx_pixel_put_image(game->mlx_img, MMAP_SPACE_COLOR,
			j + MMAP_OFFSET, i + MMAP_OFFSET);
		return ;
	}
	pixel = map[(int)(p.y / MINIMAP_CELL_SIZE)][(int)(p.x / MINIMAP_CELL_SIZE)];
	if (ft_strchr(CLOSING_ELEM, pixel))
		ft_mlx_pixel_put_image(game->mlx_img, MMAP_WALL_COLOR,
			j + MMAP_OFFSET, i + MMAP_OFFSET);
	else if (ft_strchr(INSIDE_ELEM, pixel))
		ft_mlx_pixel_put_image(game->mlx_img, game->colors[FLOOR],
			j + MMAP_OFFSET, i + MMAP_OFFSET);
	else if (ft_strchr(OUTSIDE_ELEM, pixel) || pixel)
		ft_mlx_pixel_put_image(game->mlx_img, MMAP_SPACE_COLOR,
			j + MMAP_OFFSET, i + MMAP_OFFSET);
}

static void	draw_player(t_game *game)
{
	t_pos	p;
	int		p_size;

	p_size = (MMAP_SIZE / MMAP_PLAYER_RATIO);
	p.x = MMAP_SIZE + MMAP_OFFSET - (p_size / 2);
	p.y = MMAP_SIZE + MMAP_OFFSET - (p_size / 2);
	draw_square(game->mlx_img, p, p_size, MMAP_PLAYER_COLOR);
}

void	draw_minimap(t_game *game, t_player *player)
{
	int		i;
	int		j;
	t_pos	pos;

	pos.y = roundf(player->y * (MINIMAP_CELL_SIZE / CELL_SIZE)) - MMAP_SIZE;
	i = -1;
	while (++i < MMAP_SIZE * 2)
	{
		pos.x = roundf(player->x * (MINIMAP_CELL_SIZE / CELL_SIZE)) - MMAP_SIZE;
		j = -1;
		while (++j < MMAP_SIZE * 2)
		{
			draw_circle(game, i, j, pos);
			if (pos.x < 0 || pos.y < 0
				|| (game->map.map[(int)(pos.y / MINIMAP_CELL_SIZE)]
				&& game->map.map[(int)(pos.y / MINIMAP_CELL_SIZE)] \
							[(int)(pos.x / MINIMAP_CELL_SIZE)]))
				pos.x++;
		}
		if (pos.x < 0 || pos.y < 0
			|| game->map.map[(int)(pos.y / MINIMAP_CELL_SIZE)])
			pos.y++;
	}
	draw_player(game);
}

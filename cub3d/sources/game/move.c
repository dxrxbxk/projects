/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 00:41:03 by momadani          #+#    #+#             */
/*   Updated: 2023/03/20 16:51:02 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	move_left(t_game *game)
{
	if (is_valid_move(&game->map,
			(game->player.x + game->player.dir_y) / CELL_SIZE,
			(game->player.y) / CELL_SIZE))
		game->player.x += game->player.dir_y;
	if (is_valid_move(&game->map,
			(game->player.x) / CELL_SIZE,
			(game->player.y - game->player.dir_x) / CELL_SIZE))
		game->player.y -= game->player.dir_x;
}

void	move_right(t_game *game)
{
	if (is_valid_move(&game->map,
			(game->player.x - game->player.dir_y) / CELL_SIZE,
			(game->player.y) / CELL_SIZE))
		game->player.x -= game->player.dir_y;
	if (is_valid_move(&game->map,
			(game->player.x) / CELL_SIZE,
			(game->player.y + game->player.dir_x) / CELL_SIZE))
		game->player.y += game->player.dir_x;
}

void	move_up(t_game *game)
{
	if (is_valid_move(&game->map,
			(game->player.x + game->player.dir_x) / CELL_SIZE,
			(game->player.y) / CELL_SIZE))
		game->player.x += game->player.dir_x;
	if (is_valid_move(&game->map,
			(game->player.x) / CELL_SIZE,
			(game->player.y + game->player.dir_y) / CELL_SIZE))
		game->player.y += game->player.dir_y;
}

void	move_down(t_game *game)
{
	if (is_valid_move(&game->map,
			(game->player.x - game->player.dir_x) / CELL_SIZE,
			(game->player.y) / CELL_SIZE))
		game->player.x -= game->player.dir_x;
	if (is_valid_move(&game->map,
			(game->player.x) / CELL_SIZE,
			(game->player.y - game->player.dir_y) / CELL_SIZE))
		game->player.y -= game->player.dir_y;
}

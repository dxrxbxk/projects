/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 00:40:48 by momadani          #+#    #+#             */
/*   Updated: 2023/03/20 03:39:29 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	rotate_right(t_game *game)
{
	game->player.angle += M_PI / ROTATION_SPEED_RATIO;
	if (game->player.angle > 2 * M_PI)
		game->player.angle -= 2 * M_PI;
	game->player.dir_x = cos(game->player.angle) * MOVE_SPEED;
	game->player.dir_y = sin(game->player.angle) * MOVE_SPEED;
}

void	rotate_left(t_game *game)
{
	game->player.angle -= M_PI / ROTATION_SPEED_RATIO;
	if (game->player.angle < 0)
		game->player.angle += 2 * M_PI;
	game->player.dir_x = cos(game->player.angle) * MOVE_SPEED;
	game->player.dir_y = sin(game->player.angle) * MOVE_SPEED;
}

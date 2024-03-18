/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 00:33:47 by momadani          #+#    #+#             */
/*   Updated: 2023/03/20 00:48:18 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	handle_keypress(int key, t_game *game)
{
	if (key == XK_Escape)
		game->key.k_esc = 1;
	if (key == 'w')
		game->key.k_w = 1;
	if (key == 's')
		game->key.k_s = 1;
	if (key == 'a')
		game->key.k_a = 1;
	if (key == 'd')
		game->key.k_d = 1;
	if (key == XK_Left)
		game->key.k_left = 1;
	if (key == XK_Right)
		game->key.k_right = 1;
	if (key == XK_Up)
		game->key.k_up = 1;
	if (key == XK_Down)
		game->key.k_down = 1;
	return (0);
}

int	handle_keyrelease(int key, t_game *game)
{
	if (key == XK_Escape)
		game->key.k_esc = 0;
	if (key == 'w')
		game->key.k_w = 0;
	if (key == 's')
		game->key.k_s = 0;
	if (key == 'a')
		game->key.k_a = 0;
	if (key == 'd')
		game->key.k_d = 0;
	if (key == XK_Left)
		game->key.k_left = 0;
	if (key == XK_Right)
		game->key.k_right = 0;
	if (key == XK_Up)
		game->key.k_up = 0;
	if (key == XK_Down)
		game->key.k_down = 0;
	return (0);
}

int	doaction(t_game *game)
{
	if (game->key.k_esc == 1)
		quit_game();
	if (game->key.k_w == 1)
		move_up(game);
	if (game->key.k_s == 1)
		move_down(game);
	if (game->key.k_d == 1)
		move_right(game);
	if (game->key.k_a == 1)
		move_left(game);
	if (game->key.k_left == 1)
		rotate_left(game);
	if (game->key.k_right == 1)
		rotate_right(game);
	if (game->key.k_up == 1)
		move_up(game);
	if (game->key.k_down == 1)
		move_down(game);
	put_image(game);
	return (0);
}

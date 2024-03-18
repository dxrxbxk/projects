/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:40:54 by momadani          #+#    #+#             */
/*   Updated: 2023/03/20 02:39:08 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	put_image(t_game *game)
{
	draw_game(game);
	draw_minimap(game, &game->player);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->mlx_img, 0, 0);
}

void	run(t_game *game)
{
	mlx_hook(game->mlx_win, KeyPress, KeyPressMask, &handle_keypress, game);
	mlx_hook(game->mlx_win, KeyRelease,
		KeyReleaseMask, &handle_keyrelease, game);
	mlx_hook(game->mlx_win, DestroyNotify,
		StructureNotifyMask, quit_game, NULL);
	mlx_loop_hook(game->mlx, doaction, game);
	mlx_loop(game->mlx);
}

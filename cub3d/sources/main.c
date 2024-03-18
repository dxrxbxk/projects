/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:46:50 by momadani          #+#    #+#             */
/*   Updated: 2023/03/20 03:06:17 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	quit_game(void)
{
	ft_free_game();
	exit(EXIT_SUCCESS);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
		ft_exit_error(USAGE, NULL, NULL, 1);
	ft_initgame(&game, argv[1]);
	run(&game);
	mlx_hook(game.mlx_win, DestroyNotify, StructureNotifyMask, quit_game, NULL);
	mlx_hook(game.mlx_win, KeyPress, KeyPressMask, handle_keypress, &game);
	mlx_loop(game.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:02:46 by momadani          #+#    #+#             */
/*   Updated: 2023/03/16 00:31:39 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	ft_free_map(t_map *map)
{
	ft_free_strs(map->map);
}

static void	ft_free_textures(void *mlx_ptr, t_img *textures[NB_TEXTURES])
{
	size_t	i;

	i = 0;
	while (i < NB_TEXTURES)
	{
		if (textures[i])
			mlx_destroy_image(mlx_ptr, textures[i]);
		i++;
	}
}

void	ft_free_game(void)
{
	t_game	*game;

	game = ft_memptr(NULL);
	if (!game)
		return ;
	ft_free_map(&game->map);
	ft_free_textures(game->mlx, game->textures);
	if (game->mlx_img)
		mlx_destroy_image(game->mlx, game->mlx_img);
	if (game->mlx_win)
		mlx_destroy_window(game->mlx, game->mlx_win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
}

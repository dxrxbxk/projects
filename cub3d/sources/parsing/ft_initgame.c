/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initgame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:43:03 by momadani          #+#    #+#             */
/*   Updated: 2023/03/20 17:58:02 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	ft_load_textures(void *mlx_ptr, t_img **textures, char *pathname)
{
	int		width;
	int		height;

	if (ft_strrchr(pathname, '\n'))
		*(ft_strrchr(pathname, '\n')) = '\0';
	*textures = mlx_xpm_file_to_image(mlx_ptr, pathname, &width, &height);
	if (!*textures)
		return (0);
	(*textures)->width = width;
	(*textures)->height = height;
	return (1);
}

static void	ft_init_textures(void *mlx_ptr, char *textures_paths[NB_TEXTURES],
											t_img *textures[NB_TEXTURES])
{
	if (!ft_load_textures(mlx_ptr, &(textures[NORTH]), textures_paths[NORTH]))
		(free_text_path(textures_paths),
			ft_exit_error("mlx: failed to load north texture", NULL, NULL, 4));
	if (!ft_load_textures(mlx_ptr, &(textures[SOUTH]), textures_paths[SOUTH]))
		(free_text_path(textures_paths),
			ft_exit_error("mlx: failed to load south texture", NULL, NULL, 4));
	if (!ft_load_textures(mlx_ptr, &(textures[WEST]), textures_paths[WEST]))
		(free_text_path(textures_paths),
			ft_exit_error("mlx: failed to load west texture", NULL, NULL, 4));
	if (!ft_load_textures(mlx_ptr, &(textures[EAST]), textures_paths[EAST]))
		(free_text_path(textures_paths),
			ft_exit_error("mlx: failed to load east texture", NULL, NULL, 4));
}

void	ft_init_display(char *textures_paths[NB_TEXTURES], t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		(free_text_path(textures_paths),
			ft_exit_error("mlx: failed to init display", NULL, NULL, 4));
	game->mlx_win = mlx_new_window(game->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, NAME);
	if (!game->mlx_win)
		(free_text_path(textures_paths),
			ft_exit_error("mlx: failed to create window", NULL, NULL, 4));
	game->mlx_img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->mlx_img)
		(free_text_path(textures_paths),
			ft_exit_error("mlx: failed to create image", NULL, NULL, 4));
}

int	ft_initgame(t_game *game, char *filepath)
{
	char	*textures_paths[NB_TEXTURES];
	int		fd;

	ft_memptr(game);
	ft_memset(textures_paths, 0, (sizeof(char *) * NB_TEXTURES));
	game->colors[0] = 1L << 31;
	game->colors[1] = 1L << 31;
	fd = ft_statfile(filepath);
	ft_parsefile(game, fd, textures_paths);
	if (close(fd) == -1)
		(free_text_path(textures_paths),
			ft_exit_error("close: ", strerror(errno), NULL, -1));
	ft_parsemap(&game->map, &game->player, textures_paths);
	ft_init_display(textures_paths, game);
	ft_init_textures(game->mlx, textures_paths, game->textures);
	free_text_path(textures_paths);
	return (0);
}

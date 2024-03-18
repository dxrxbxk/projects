/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 02:11:08 by momadani          #+#    #+#             */
/*   Updated: 2023/03/20 17:58:19 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* --------------------------------libraries--------------------------------- */

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <X11/X.h>
# include <X11/keysym.h>

# include <mlx.h>
# include <mlx_int.h>

/* --------------------------------constants--------------------------------- */

# define USAGE "Usage: ./cub3D <map.cub>"

# define NAME "cub3D"

# define CELL_SIZE 64.f
# define MINIMAP_CELL_SIZE 36.f

# define WHITE_SPACES "\t "
# define PLAYER_ELEM "NSEW"
# define VALID_ELEM " 01NSEW"
# define INSIDE_ELEM "0NSEW"
# define OUTSIDE_ELEM " "
# define CLOSING_ELEM "1"

# define NB_TEXTURES 4

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

# define FLOOR 0
# define CEIL 1

# define WINDOW_WIDTH 1200
# define WINDOW_HEIGHT 1000
# define FOV 45

# define PLAYER_COLOR 0xff0000
# define WALL_COLOR 0x453b32
# define FREE_SPACE_COLOR 0x668666

# define ROTATION_SPEED_RATIO 66
# define MOVE_SPEED 6

# define H 0
# define V 1

# define WALL_HEIGHT 1200
# define DIST_PROJ_PLANE 60

# define MAX_DIST 10000
# define MAX_DOF 50

# define MMAP_SIZE 90
# define MMAP_PLAYER_RATIO 10
# define MMAP_OFFSET 40

# define MMAP_CIRCLE_COLOR 0x00ffffff
# define MMAP_PLAYER_COLOR 0x000000ff
# define MMAP_WALL_COLOR 0x00101020
# define MMAP_SPACE_COLOR 0x00ffff99

/* --------------------------------structures-------------------------------- */

typedef int	t_pos	__attribute__((ext_vector_type(2)));

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
}				t_map;

typedef struct s_display
{
	int	wall_height;
	int	wall_top;
	int	wall_bottom;
	int	tex_x;
	int	tex_y;
	int	color;
}				t_display;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	double	dir_x;
	double	dir_y;
}				t_player;

typedef struct s_inter
{
	double	rx;
	double	ry;
	double	ra;
	double	xo;
	double	yo;
	int		hit;
}				t_inter;

typedef struct s_keys
{
	int		k_w;
	int		k_s;
	int		k_d;
	int		k_a;
	int		k_left;
	int		k_right;
	int		k_up;
	int		k_down;
	int		k_esc;
}				t_keys;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	t_img		*mlx_img;
	t_img		*textures[NB_TEXTURES];
	uint32_t	colors[2];
	t_player	player;
	t_map		map;
	t_inter		data[2];
	t_keys		key;
	bool		is_horizontal;
}				t_game;

/* ---------------------------------parsing---------------------------------- */

int		ft_parsemap(t_map *map, t_player *player,
			char *textures_paths[NB_TEXTURES]);
int		ft_check_outside_surrounding(char **map, int x, int y);
int		ft_check_inside_surrounding(char **map, int x, int y);
int		ft_parsefile(t_game *game, int fd, char *textures_paths[NB_TEXTURES]);
int		ft_initgame(t_game *game, char *filepath);
int		ft_statfile(char *filepath);
int		ft_extract_textcol(t_game *game, char *line,
			char *textures_paths[NB_TEXTURES], int fd);
int		is_color_type(char *s);
int		get_color(char *line, uint32_t colors[2],
			char *path[NB_TEXTURES], int fd);
void	ft_skip_whitespaces(char **s);
double	init_angle(char direction);

/* -----------------------------------mlx------------------------------------ */

void	ft_mlx_pixel_put_image(t_img *img, unsigned int color, int x, int y);
int		mlx_get_pixel_color(t_img *img, int x, int y);

/* -----------------------------------game----------------------------------- */

void	run(t_game *game);
void	draw_minimap(t_game *game, t_player *player);
int		color_multiplier(int color, float multiplier);
void	draw_square(t_img *image, t_pos p, int size, int color);

			/*---------------------raycasting---------------------*/

void	draw_game(t_game *game);
void	draw_ray(t_game *game, int x, double ray_angle, double distance);
void	put_image(t_game *game);

			/*-----------------------events-----------------------*/

int		handle_keypress(int key, t_game *game);
int		handle_keyrelease(int key, t_game *game);
int		doaction(t_game *game);
int		quit_game(void);

			/*----------------------movement-----------------------*/

void	move_player(int dx, int dy, t_game *game);
void	move_up(t_game *game);
void	move_down(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);

void	rotate_right(t_game *game);
void	rotate_left(t_game *game);

			/*--------------------intersection--------------------*/

double	find_vertical(double px, double py, double ra, t_game *game);
double	find_horizontal(double px, double py, double ra, t_game *game);
double	find_next_intersection(t_game *game, double ra, t_inter *data);

			/*-----------------------checks-----------------------*/

bool	is_within_bounds(t_map *map, int x, int y);
bool	is_wall(t_map *map, int x, int y);
bool	is_valid_move(t_map *map, int x, int y);
bool	is_adjacent(t_map *map, int x, int y);

/* ----------------------------------memory---------------------------------- */

void	ft_free_game(void);
void	ft_free_strs(char **strs);
void	free_text_path(char *path[NB_TEXTURES]);
t_game	*ft_memptr(t_game *addr);

/* ----------------------------------utils----------------------------------- */

void	ft_exit_error(char *msg1, char *msg2, char *msg3, int exit_status);
char	*ft_mega_join(char *s1, char *s2, char *s3);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putstr_fd(char const *s, int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strcat(char *dst, const char *src);
char	*ft_strdup(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char const *charset);
char	**ft_split_whitespace(char const *s);
size_t	ft_strs_len(char **strs);
int		ft_strlen(const char *s);

/* ------------------------------get-next-line------------------------------- */

# define BUFFER_SIZE 1

size_t	ft_strclen(const char *s, char c);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strjoin(char *s1, char const *s2);
char	*get_next_line(int fd);

#endif

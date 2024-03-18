/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:00:42 by diroyer           #+#    #+#             */
/*   Updated: 2022/01/13 11:28:47 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "mlx/mlx.h"
# include <stdio.h>
# include <X11/X.h>
# include <unistd.h>
# include <stdlib.h>
# define WIN_X 2000
# define WIN_Y 1000
# define ZOOM 200
# define MAXITER 250

typedef struct s_julia
{
	double	c1;
	double	c2;
}				t_julia;

typedef struct s_data
{
	void	*img;
	void	*mlx;
	void	*win;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	posx;
	double	posy;
	int		zoom;
	int		zoomx;
	int		zoomy;
	double	j1;
	double	j2;
	int		n;
	int		(*fractol[2])(struct s_data *, double, double);
}				t_data;
// main.c
void	put_image(t_data *data, int (*f)(t_data *, double, double));

// mandelbrot.c
int		mandelbrot(t_data *data, double c1, double c2);

// julia.c
int		julia(t_data *data, double c1, double c2);

// utils.c
void	print_error(void);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		close_win(int keycode, t_data *data);
int		get_color(int i);
int		mouse_hook(int keycode, int x, int y, t_data *data);

// ft_atof.c
double	ft_atof(const char *nptr);

#endif

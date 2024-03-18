/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:03:59 by diroyer           #+#    #+#             */
/*   Updated: 2022/01/13 13:34:34 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_image(t_data *data, int (*f)(t_data *, double, double))
{
	int		posx;
	int		posy;
	int		i;

	posx = 0;
	i = 0;
	while (posx <= WIN_X)
	{
		posy = 0;
		while (posy <= WIN_Y)
		{
			i = f(data, posx, posy);
			if (i == MAXITER)
				my_mlx_pixel_put(data, posx, posy, 0);
			else
				my_mlx_pixel_put(data, posx, posy, get_color(i));
			posy++;
		}
		posx++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

static void	init_image(int n, t_julia *juliadata)
{
	t_data	data;

	data.fractol[0] = &mandelbrot;
	data.fractol[1] = &julia;
	data.n = n;
	data.zoom = 250;
	data.j1 = juliadata->c1;
	data.j2 = juliadata->c2;
	data.posx = 0;
	data.posy = 0;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIN_X, WIN_Y, "Fractol");
	data.img = mlx_new_image(data.mlx, WIN_X, WIN_Y);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	put_image(&data, data.fractol[data.n]);
	mlx_hook(data.win, KeyPress, KeyPressMask, &close_win, &data);
	mlx_mouse_hook(data.win, mouse_hook, &data);
	mlx_loop(data.mlx);
}

static int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

static void	fill_julia(t_julia *data, double j1, double j2)
{
	data->c1 = j1;
	data->c2 = j2;
}

#include <string.h>

int	main(int ac, char **av)
{
	t_julia	data;
	memset(&data, 0, sizeof(t_julia));

	if (ac > 1)
	{
		if (ft_strcmp(av[1], "mandelbrot") == 0 && ac == 2)
		{
			init_image(0, &data);
		}
		else if (ft_strcmp(av[1], "julia") == 0 && (ac == 2 || ac == 4))
		{
			if (ac == 4)
				fill_julia(&data, ft_atof(av[2]), ft_atof(av[3]));
			if (ac == 2)
				fill_julia(&data, -1.476, 0.0);
			init_image(1, &data);
		}
		else
			print_error();
	}
	else
		print_error();
}

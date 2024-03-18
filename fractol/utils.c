/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:44:41 by diroyer           #+#    #+#             */
/*   Updated: 2022/01/13 13:02:16 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_win(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(0);
	}	
	return (1);
}

int	get_color(int i)
{
	const int	blue[19] = {0x000066, 0x00099, 0x0000CC, 0x0000FF,
		0x3333FF, 0x3399ff, 0x0080ff, 0x0066ff, 0x004c99,
		0xCC99ff, 0xb266ff, 0x9933ff, 0x7f00ff, 0x6600cc,
		0xffcc99, 0xffb266, 0xff9933, 0xff8000, 0xcc6600};

	i = i % 19;
	return (blue[i]);
}

int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (keycode == 4)
	{
		data->zoom += 250;
		put_image(data, data->fractol[data->n]);
	}	
	if (keycode == 5)
	{
		data->zoom -= 100;
		if (data->zoom < 0)
			data->zoom = 0;
		put_image(data, data->fractol[data->n]);
	}
	return (1);
}

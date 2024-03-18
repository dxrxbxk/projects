/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 18:37:36 by diroyer           #+#    #+#             */
/*   Updated: 2023/03/20 18:01:53 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_square(t_img *image, t_pos p, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_mlx_pixel_put_image(image, color, p.x + j, p.y + i);
			j++;
		}
		i++;
	}
}

void	ft_mlx_pixel_put_image(t_img *img, unsigned int color, int x, int y)
{
	char	*target;

	if (x < 0 || y < 0)
		return ;
	target = img->data + ((x * img->bpp / 8) + (y * img->size_line));
	*(unsigned int *)target = color;
}

int	mlx_get_pixel_color(t_img *img, int x, int y)
{
	if (x < 0 || y < 0)
		return (0);
	return (*(int *)
		(img->data + ((x * img->bpp / 8) + (y * img->size_line))));
}

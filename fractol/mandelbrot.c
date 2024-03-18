/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:50:34 by diroyer           #+#    #+#             */
/*   Updated: 2022/01/13 12:30:13 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot(t_data *data, double c1, double c2)
{
	int		i;
	double	za;
	double	zb;
	double	tmp;

	c1 = ((c1 - WIN_X / 2) / data->zoom);
	c2 = (- (c2 - WIN_Y / 2) / data->zoom);
	i = 0;
	za = 0;
	zb = 0;
	while (za * za + zb * zb <= 4 && i < MAXITER)
	{
		tmp = za;
		za = tmp * tmp - zb * zb + c1;
		zb = 2 * tmp * zb + c2;
		i++;
	}
	return (i);
}

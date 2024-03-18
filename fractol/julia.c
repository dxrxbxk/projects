/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:51:17 by diroyer           #+#    #+#             */
/*   Updated: 2022/01/13 13:33:03 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia(t_data *data, double c1, double c2)
{
	int		i;
	double	za;
	double	zb;
	double	tmp;

	za = (c1 - WIN_X / 2) / data->zoom;
	zb = - (c2 - WIN_Y / 2) / data->zoom;
	i = 0;
	c1 = data->j1;
	c2 = data->j2;
	while (za * za + zb * zb <= 4 && i < MAXITER)
	{
		tmp = za;
		za = tmp * tmp - zb * zb + c1;
		zb = 2 * tmp * zb + c2;
		i++;
	}
	return (i);
}

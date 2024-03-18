/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:04:50 by diroyer           #+#    #+#             */
/*   Updated: 2022/01/13 11:15:02 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	print_error(void)
{
	ft_putstr("Usage :\n");
	ft_putstr("./fractol mandelbrot/julia\n");
}

static double	fill_result(double *result, const char **nptr, int *i)
{
	int	e;

	e = 0;
	while ((*nptr)[(*i)] >= '0' && (*nptr)[(*i)] <= '9')
		(*result) = (*result) * 10.0 + ((*nptr)[(*i)++] - '0');
	if ((*nptr)[(*i)] == '.')
		(*i)++;
	while ((*nptr)[(*i)] >= '0' && (*nptr)[(*i)] <= '9')
	{
		(*result) = (*result) * 10.0 + ((*nptr)[(*i)++] - '0');
		e--;
	}
	while (e < 0)
	{
		*result = *result * 0.1;
		e++;
	}
	return (*result);
}

double	ft_atof(const char *nptr)
{
	double	result;
	int		sign;
	int		i;

	i = 0;
	result = 0.0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	result = fill_result(&result, &nptr, &i);
	return (result * sign);
}

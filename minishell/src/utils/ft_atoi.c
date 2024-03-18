/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:04:50 by diroyer           #+#    #+#             */
/*   Updated: 2021/11/25 18:05:56 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#define LONG_MAX 0x7fffffffffffffff

int	ft_atoi(const char *nptr)
{
	unsigned long long	result;
	int					sign;
	size_t				i;

	i = 0;
	result = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
		result = result * 10 + (nptr[i++] - '0');
	if (result >= LONG_MAX && sign == 1)
		result = -1;
	if (result > LONG_MAX && sign == -1)
		result = 0;
	if (result < LONG_MAX && result > 2147483647)
		result = result - LONG_MAX - 1;
	return (result * sign);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:44:47 by diroyer           #+#    #+#             */
/*   Updated: 2021/11/29 11:16:05 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_len(long nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

static void	ft_is_neg(long *n, int *len, int *sign)
{
	if ((*n) < 0)
	{
		(*n) = -(*n);
		(*len)++;
		*sign = 1;
	}
}

char	*ft_itoa(int nb)
{
	char	*array;
	int		len;
	int		sign;
	long	n;

	n = nb;
	len = 0;
	sign = 0;
	len = ft_len(n);
	ft_is_neg(&n, &len, &sign);
	array = malloc(len + 1);
	if (!array)
		return (NULL);
	array[len] = '\0';
	while (len--)
	{
		array[len] = (n % 10) + 48;
		n /= 10;
	}
	if (sign == 1)
		array[0] = '-';
	return (array);
}

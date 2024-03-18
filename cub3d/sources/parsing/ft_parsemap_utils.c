/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsemap_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:36:49 by momadani          #+#    #+#             */
/*   Updated: 2023/03/18 18:39:29 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	increment(int *i, int *j, int x, int k)
{
	if (k % 3 == 0)
	{
		*j = x - 1;
		(*i)++;
	}
	else
		(*j)++;
}

int	ft_check_inside_surrounding(char **map, int x, int y)
{
	int	i;
	int	j;
	int	k;

	i = y - 1;
	j = x - 1;
	k = 0;
	while (k < 9)
	{
		k++;
		if (i < 0 || j < 0 || !map[i] || ft_strlen(map[i]) < j || !map[i][j])
			break ;
		else if (k == 1 || k == 3 || k == 7 || k == 9)
			increment(&i, &j, x, k);
		else if (ft_strchr(CLOSING_ELEM, map[i][j]))
			increment(&i, &j, x, k);
		else if (ft_strchr(INSIDE_ELEM, map[i][j]))
			increment(&i, &j, x, k);
		else if (ft_strchr(OUTSIDE_ELEM, map[i][j]) || map[i][j] == '\n')
			break ;
	}
	return (k == 9);
}

int	ft_check_outside_surrounding(char **map, int x, int y)
{
	int	i;
	int	j;
	int	k;

	i = y - 1;
	j = x - 1;
	k = 0;
	while (k < 9)
	{
		k++;
		if (i < 0 || j < 0 || !map[i] || ft_strlen(map[i]) < j || !map[i][j])
			increment(&i, &j, x, k);
		else if (k == 1 || k == 3 || k == 7 || k == 9)
			increment(&i, &j, x, k);
		else if (ft_strchr(CLOSING_ELEM, map[i][j]))
			increment(&i, &j, x, k);
		else if (ft_strchr(OUTSIDE_ELEM, map[i][j]) || map[i][j] == '\n')
			increment(&i, &j, x, k);
		else if (ft_strchr(INSIDE_ELEM, map[i][j]))
			break ;
	}
	return (k == 9);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mega_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:05:58 by diroyer           #+#    #+#             */
/*   Updated: 2023/02/22 23:28:21 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

char	*ft_mega_join(char *s1, char *s2, char *s3)
{
	size_t	len;
	char	*array;

	if (!s1 && !s2 && !s3)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	array = malloc(sizeof(char) * (len + 1));
	if (!array)
		return (NULL);
	array[0] = '\0';
	ft_strcpy(array, s1);
	ft_strcat(array, s2);
	ft_strcat(array, s3);
	return (array);
}

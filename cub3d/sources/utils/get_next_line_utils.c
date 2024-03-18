/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 13:36:21 by momadani          #+#    #+#             */
/*   Updated: 2023/03/15 17:54:37 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

size_t	ft_strclen(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s && s[len] && s[len++] != c)
		;
	return (len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	if (!dst || !src)
		return (0);
	i = 0;
	while (dst[i] && i < size)
		i++;
	if (i == size)
		return (size + ft_strclen(src, '\0'));
	j = 0;
	while (size && src[j] && (i + j) < (size - 1))
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i + j < size)
		dst[i + j] = '\0';
	return (ft_strclen(src, '\0') + i);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*dest;
	size_t	size;

	size = ft_strclen(s1, '\0') + ft_strclen(s2, '\0');
	dest = malloc((size + 1) * sizeof(char));
	if (!(dest))
		return (NULL);
	*dest = '\0';
	ft_strlcat(dest, s1, (size + 1));
	ft_strlcat(dest, s2, (size + 1));
	free(s1);
	return (dest);
}

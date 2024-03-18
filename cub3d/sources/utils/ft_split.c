/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:58:36 by momadani          #+#    #+#             */
/*   Updated: 2023/03/14 21:23:18 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static int	ft_toklen(char const *s, char const *charset)
{
	int	len;

	len = 0;
	while (s[len] && !ft_strchr(charset, s[len]))
		len++;
	return (len);
}

static int	ft_tokcount(char const *s, char const *charset)
{
	int	len;

	len = 0;
	while (*s)
	{
		while (*s && ft_strchr(charset, *s))
			s++;
		if (*s)
			len++;
		s += ft_toklen(s, charset);
	}
	return (len);
}

static char	*ft_strtok(char const *s, int *rank, char const *charset)
{
	char	*dest;
	int		i;

	dest = malloc(sizeof(char) * (ft_toklen(s, charset) + 1));
	if (!(dest))
		return (NULL);
	i = 0;
	while (s[i] && !ft_strchr(charset, s[i]))
	{
		dest[i] = s[i];
		i++;
		(*rank)++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	**ft_free(char **strs, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char const *charset)
{
	char	**strs;
	int		i;
	int		j;

	strs = malloc(sizeof(char *) * (ft_tokcount(s, charset) + 1));
	if (!(strs))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && ft_strchr(charset, s[i]))
			i++;
		if (s[i])
		{
			strs[j] = ft_strtok(&s[i], &i, charset);
			if (strs[j] == NULL)
				return (ft_free(strs, (ft_tokcount(s, charset) + 1)));
			j++;
		}
	}
	strs[j] = NULL;
	return (strs);
}

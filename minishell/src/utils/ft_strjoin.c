/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:50:18 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/14 15:40:08 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*array;

	if (!s1 && !s2)
		return (NULL);
	len = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	array = malloc(sizeof(char) * (len + 1));
	if (!array)
		return (NULL);
	ft_strlcpy(array, s1, ft_strlen(s1) + 1);
	ft_strlcat(array, s2, len + 1);
	return (array);
}

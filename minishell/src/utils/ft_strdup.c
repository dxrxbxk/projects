/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:28:25 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/11 20:11:26 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strdup(const char *s1)
{
	char	*array;
	size_t	i;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	array = malloc(sizeof(char) * (i + 1));
	if (!array)
		return (NULL);
	ft_strlcpy(array, s1, i + 1);
	return (array);
}

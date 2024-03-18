/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:28:25 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/08 16:43:32 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strndup(const char *s1, int len)
{
	char	*array;

	if (len < 0)
		return (NULL);
	array = malloc(sizeof(char) * (len + 1));
	if (!array)
		return (NULL);
	ft_strlcpy(array, s1, len + 1);
	return (array);
}

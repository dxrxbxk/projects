/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 06:00:55 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/21 13:36:52 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_child	**ft_memptr_child(t_child **child)
{
	static t_child	**ptr = NULL;

	if (child)
		ptr = child;
	return (ptr);
}

t_mini	**ft_memptr_data(t_mini **data)
{
	static t_mini	**ptr = NULL;

	if (data)
		ptr = data;
	return (ptr);
}

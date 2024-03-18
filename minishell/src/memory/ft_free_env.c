/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:12:49 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/21 14:13:38 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_env_delone(t_env *elem)
{
	free(elem->key);
	free(elem->value);
	free(elem);
}

void	free_env(t_env *lst)
{
	t_env	*tmp;

	tmp = NULL;
	while (lst)
	{
		tmp = (lst)->next;
		ft_env_delone(lst);
		lst = tmp;
	}
}

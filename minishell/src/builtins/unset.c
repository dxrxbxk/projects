/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 01:21:49 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/23 06:05:24 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	del_and_link(t_env **lst, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	prev = *lst;
	tmp = *lst;
	if (tmp != NULL && !ft_strcmp(tmp->key, key))
	{
		*lst = tmp->next;
		ft_env_delone(tmp);
		return ;
	}
	while (tmp != NULL && ft_strcmp(tmp->key, key))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = tmp->next;
	ft_env_delone(tmp);
}

int	ft_unset(t_env **lst, char **av, int ac)
{
	int		i;

	i = 0;
	while (++i < ac)
	{
		if (get_env_key(*lst, av[i]))
			del_and_link(lst, av[i]);
	}
	return (0);
}

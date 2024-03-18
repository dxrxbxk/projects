/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:27:55 by diroyer           #+#    #+#             */
/*   Updated: 2023/02/10 05:25:11 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	print_env_export(t_env *print)
{
	t_env	*tmp;

	tmp = lst_copy(print);
	sort_list(tmp);
	while (tmp)
	{
		if (tmp->value)
		{
			if (printf("export %s=\"%s\"\n", tmp->key, tmp->value) < 0)
			{
				ft_error("export: write error: ", strerror(errno), NULL, 1);
				return -1;
			}
		}
		else if (tmp->key)
		{
			if (printf("export %s\n", tmp->key) < 0)
			{
				ft_error("export: write error: ", strerror(errno), NULL, 1);
				return -1;
			}
		}
		tmp = tmp->next;
	}
	return (free_env(tmp), 0);
}

t_env	*lst_copy(t_env *lst)
{
	t_env	*first;
	t_env	*elem;

	first = NULL;
	while (lst)
	{
		elem = ft_env_new(lst->key, lst->value);
		if (!elem)
			return (NULL);
		ft_env_addback(&first, elem);
		lst = lst->next;
	}
	return (first);
}

void	sort_list(t_env *lst)
{
	t_env	*cmp;

	cmp = lst;
	while (lst)
	{
		if (lst->next)
			cmp = lst->next;
		while (cmp)
		{
			if (ft_strcmp(lst->key, cmp->key) > 0)
			{
				ft_swap_str(&lst->key, &cmp->key);
				ft_swap_str(&lst->value, &cmp->value);
			}
			cmp = cmp->next;
		}
		lst = lst->next;
	}
}

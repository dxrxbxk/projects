/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:19:46 by diroyer           #+#    #+#             */
/*   Updated: 2023/02/10 06:51:43 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_mini	*get_env_path(t_env *lst, t_mini *data)
{
	if (ft_strcmp(get_key_value(lst, "PATH"), data->path))
	{
		if (data->spath)
			free_tab(&data->spath);
		data->spath = ft_split(get_key_value(lst, "PATH"), ':');
	}
	return (data);
}

void	create_env_node(t_env **first, void *key, void *value)
{
	t_env	*new;

	new = ft_env_new(key, value);
	if (!new)
		return ;
	ft_env_addback(first, new);
}

void	ft_env_addback(t_env **first, t_env *new)
{
	t_env	*current;

	current = *first;
	if (!*first)
		*first = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

t_env	*ft_env_new(void *key, void *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

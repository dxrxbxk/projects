/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:24:57 by diroyer           #+#    #+#             */
/*   Updated: 2023/02/10 06:04:42 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	print_env(t_env *print)
{
	while (print)
	{
		if (print->value != NULL && *print->key != '\0')
		{
			if (printf("%s=%s\n", print->key, print->value) < 0)
			{
				ft_error("env: write error: ", strerror(errno), NULL, 125);
				return (-1);
			}
		}
		print = print->next;
	}
	return (0);
}

char	*get_key_value(t_env *lst, char *get)
{
	while (lst)
	{
		if (!ft_strcmp(lst->key, get))
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

char	*get_env_key(t_env *lst, char *get)
{
	while (lst)
	{
		if (!ft_strcmp(lst->key, get))
			return (lst->key);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_join_env(t_env *lst, char *cmp, char *value)
{
	char	*tmp;

	while (lst)
	{
		if (!ft_strcmp(lst->key, cmp))
		{
			free(cmp);
			tmp = lst->value;
			lst->value = ft_strjoin(lst->value, value);
			free(tmp);
			free(value);
		}
		lst = lst->next;
	}
}

void	ft_replace_env(t_env *lst, char *cmp, char *value)
{
	while (lst)
	{
		if (!ft_strcmp(lst->key, cmp))
		{
			free(lst->value);
			lst->value = NULL;
			lst->value = value;
		}
		lst = lst->next;
	}
}

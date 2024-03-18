/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:40:44 by diroyer           #+#    #+#             */
/*   Updated: 2023/02/10 07:04:25 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	export_key(char *str, int *join)
{
	int	i;

	i = 0;
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (-1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (str[i] == '+' && str[i + 1] == '=')
	{
		*join = 1;
		return (i + 1);
	}
	else if (str[i] == '=')
		return (i);
	else if (str[i] == '\0')
		return (0);
	return (-1);
}

static void	free_key_value(char *key, char *value)
{
	free(key);
	free(value);
}

static void	fill_env(t_env **lst, char *av, int join)
{
	char	*key;
	char	*value;

	if (!join)
		key = ft_strndup(av, ft_findi(av, '='));
	else
		key = ft_strndup(av, ft_findi(av, '+'));
	if (ft_strchr(av, '='))
		value = ft_strdup(ft_strchr(av, '=') + 1);
	else
		value = NULL;
	if (get_env_key(*lst, key) && join == 1)
		ft_join_env(*lst, key, value);
	else if (get_env_key(*lst, key) && join == 0 && ft_strchr(av, '='))
	{
		ft_replace_env(*lst, key, value);
		free(key);
	}
	else if (!get_env_key(*lst, key))
		create_env_node(lst, key, value);
	else
		free_key_value(key, value);
}

int	ft_export(t_env **lst, char **av, int ac)
{
	int		i;
	int		join;

	i = 0;
	join = 0;
	if (ac == 1)
	{
		if (print_env_export(*lst) == -1)
			return (1);
	}
	while (++i < ac)
	{
		if (export_key(av[i], &join) >= 0)
			fill_env(lst, av[i], join);
		else
			ft_error("export: `", av[i], "': not a valid identifier", 1);
	}
	return (0);
}

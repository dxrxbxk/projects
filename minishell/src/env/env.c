/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:07:13 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/23 02:28:58 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#define SHLVL_WARNING "warning: shell level (1000) too high, resetting to 1"

char	*ret_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	return (cwd);
}

char	**create_env(void)
{
	char	**env;
	char	*cwd;

	cwd = ret_pwd();
	if (!cwd)
		return (NULL);
	env = malloc(sizeof(char *) * 3);
	if (!env)
		return (NULL);
	env[0] = ft_strjoin("PWD=", cwd);
	env[1] = ft_strjoin("SHLVL=", "0");
	env[2] = NULL;
	free(cwd);
	return (env);
}

int	get_env(t_mini *data, char **env)
{
	t_env	**elm;
	int		i;

	elm = &data->env;
	i = -1;
	if (!env)
		return (-1);
	while (env[++i])
	{
		*elm = malloc(sizeof(t_env));
		if (!*elm)
			return (-1);
		(*elm)->key = ft_strndup(env[i], ft_findi(env[i], '='));
		if (!(*elm)->key)
			return (-1);
		(*elm)->value = ft_strdup(ft_strchr(env[i], '=') + 1);
		if (!(*elm)->value)
			return (-1);
		elm = &((*elm)->next);
		(*elm) = NULL;
	}
	return (0);
}

int	get_path(t_mini *data, char **env)
{
	int		i;

	i = 0;
	data->spath = NULL;
	data->path = NULL;
	if (!env)
		return (-1);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			data->path = ft_strdup(ft_strchr(env[i], '=') + 1);
			if (!data->path)
				return (-1);
			data->spath = ft_split(data->path, ':');
			if (!data->spath)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	get_shlvl(t_mini *data)
{
	char	*value;
	int		ret;

	if (!get_key_value(data->env, "SHLVL"))
		create_env_node(&data->env, "SHLVL", "0");
	value = ft_strdup(get_key_value(data->env, "SHLVL"));
	if (!value)
		return (-1);
	ret = ft_atoi(value) + 1;
	if (ret > 999)
	{
		ft_error(SHLVL_WARNING, NULL, NULL, 0);
		ret = 1;
	}
	free(value);
	value = ft_itoa(ret);
	if (!value)
		return (-1);
	ft_replace_env(data->env, "SHLVL", value);
	return (0);
}

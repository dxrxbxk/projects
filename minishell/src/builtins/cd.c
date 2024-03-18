/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:34:03 by diroyer           #+#    #+#             */
/*   Updated: 2023/02/10 07:00:16 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	cd_error(char *av)
{
	char	*error;

	error = ft_strjoin(av, ": ");
	if (!error)
		return (1);
	ft_error("cd: ", error, strerror(errno), 1);
	free(error);
	return (1);
}

static void	replace_old_pwd(t_env **lst)
{
	char	*replace;
	t_env	*new;

	replace = ft_strdup(get_key_value(*lst, "PWD"));
	if (errno == ENOMEM)
	{
		ft_error("pwd: ", strerror(errno), NULL, errno);
		return ;
	}
	if (!get_key_value(*lst, "OLDPWD"))
	{
		new = ft_env_new(ft_strdup("OLDPWD"), replace);
		ft_env_addback(lst, new);
	}
	else
		ft_replace_env(*lst, "OLDPWD", replace);
}

static void	replace_pwd(char *replace, t_env **lst)
{
	char	*cwd;
	t_env	*new;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	replace_old_pwd(lst);
	if (!get_key_value(*lst, replace))
	{
		new = ft_env_new(ft_strdup(replace), cwd);
		ft_env_addback(lst, new);
	}
	else
		ft_replace_env(*lst, replace, cwd);
}

static int	ft_cd_old(t_env **lst)
{
	if (get_key_value(*lst, "OLDPWD") && !chdir(get_key_value(*lst, "OLDPWD")))
	{
		replace_pwd("PWD", lst);
		printf("%s\n", get_key_value(*lst, "PWD"));
	}
	else if (!get_key_value(*lst, "OLDPWD"))
		return (ft_error("cd: OLDPWD not set", NULL, NULL, 1), 1);
	else
		return (cd_error(get_key_value(*lst, "OLDPWD")));
	return (0);
}

static int	ft_cd_home(t_env **lst)
{
	if (get_key_value(*lst, "HOME") && chdir(get_key_value(*lst, "HOME")))
		return (ft_error("cd: HOME not set", NULL, NULL, 1), 1);
	else
		ft_replace_env(*lst, "PWD", ft_strdup(get_key_value(*lst, "HOME")));
	return (0);
}

int	ft_cd(t_env **lst, char **av, int ac)
{
	if (ac == 1)
		return (ft_cd_home(lst));
	else if (ac == 2)
	{
		if (!strcmp(av[1], "-"))
			return (ft_cd_old(lst));
		else if (!chdir(av[1]))
			replace_pwd("PWD", lst);
		else
			return (cd_error(av[1]));
	}
	else
		return (ft_error("cd: too many arguments", NULL, NULL, 1));
	return (0);
}

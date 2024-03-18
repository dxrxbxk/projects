/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:44:24 by diroyer           #+#    #+#             */
/*   Updated: 2023/02/10 06:54:56 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(t_env **lst, char **av, int ac)
{
	char	*cwd;
	t_env	*new;

	(void)av;
	(void)ac;
	if (get_key_value(*lst, "PWD"))
	{
		if (printf("%s\n", get_key_value(*lst, "PWD")) < 0)
			return (ft_error("pwd : write error: ", strerror(errno), NULL, 1), 1);
	}
	else
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (ft_error("pwd: ", strerror(errno), NULL, 1));
		new = ft_env_new(ft_strdup("PWD"), cwd);
		if (!new)
			return (1);
		ft_env_addback(lst, new);
		if (printf("%s\n", get_key_value(*lst, "PWD")) < 0)
			return (ft_error("pwd : write error: ", strerror(errno), NULL, 1), 1);
	}
	return (0);
}

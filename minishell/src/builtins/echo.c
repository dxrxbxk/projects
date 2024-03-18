/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:03:29 by diroyer           #+#    #+#             */
/*   Updated: 2023/02/10 05:04:18 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_cmpchar(char *str, char c)
{
	int	i;

	i = -1;
	if (!str || !*str)
		return (1);
	while (str[++i])
	{
		if (str[i] != c)
			return (1);
	}
	return (0);
}

static int	ft_echo_print(char **av, int ac, int i, int n)
{
	while (i < ac)
	{
		if (ft_putstr_fdr(av[i], 1) == 1)
		{
			ft_error("echo: write error: ", strerror(errno), NULL, 1);
			return (1);
		}
		if (i++ + 1 < ac)
			ft_putchar_fd(' ', 1);
	}
	if (n)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	ft_echo(t_env **lst, char **av, int ac)
{
	int	i;

	i = 1;
	(void)lst;
	if (ac == 1)
		ft_putstr_fd("\n", 1);
	if (ac > 1 && av[1][0] == '-' && !ft_cmpchar(av[1] + 1, 'n'))
	{
		while (i < ac && strlen(av[i]) > 1 && av[i][0] == '-'
					&& !ft_cmpchar(av[i] + 1, 'n'))
			i++;
		return (ft_echo_print(av, ac, i, 0));
	}
	else if (ac > 1)
		return (ft_echo_print(av, ac, i, 1));
	return (0);
}

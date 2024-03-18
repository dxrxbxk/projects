/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:33:59 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/21 14:30:53 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_error(char *msg, char *var, char *msg2, int ret)
{
	char	*print;
	char	*tmp;

	tmp = ft_mega_join(msg, var, msg2);
	if (!tmp)
		return (1);
	print = ft_mega_join("minish: ", tmp, "\n");
	if (!print)
		return (1);
	ft_putstr_fd(print, 2);
	free(print);
	free(tmp);
	if (ret != -1)
		g_status = ret;
	return (ret);
}

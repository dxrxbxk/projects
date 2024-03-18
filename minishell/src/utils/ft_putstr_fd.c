/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:06:16 by diroyer           #+#    #+#             */
/*   Updated: 2023/02/10 04:47:17 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL) {
		if (write(fd, s, ft_strlen(s)) == -1) {
			ft_error(NULL, strerror(errno), NULL, 1);
		}
	}
}

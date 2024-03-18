/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:55:13 by momadani          #+#    #+#             */
/*   Updated: 2023/03/20 03:25:45 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	ft_exit_error(char *msg1, char *msg2, char *msg3, int exit_status)
{
	char	*error_message;
	char	*tmp;

	tmp = ft_mega_join(msg1, msg2, msg3);
	if (!tmp)
		exit(-1);
	error_message = ft_mega_join("Error\ncub3D: ", tmp, "\n");
	if (!error_message)
		(free(tmp), exit(-1));
	ft_putstr_fd(error_message, STDERR_FILENO);
	free(tmp);
	free(error_message);
	ft_free_game();
	exit(exit_status);
}

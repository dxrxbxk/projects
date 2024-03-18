/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:17:28 by diroyer           #+#    #+#             */
/*   Updated: 2022/12/08 23:23:39 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/sysmacros.h>
# define MEM_ERROR "Memory allocation failed"
# include <struct.h>
# include <env.h>
# include <lexer.h>
# include <parsing.h>
# include <utils.h>
# include <builtins.h>
# include <signals.h>
# include <exec.h>
# include <memory.h>
# include <sys/ioctl.h>

extern int	g_status;

void	print_tab(char **tab);
int		tab_len(char **av);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:28:49 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/23 02:28:35 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# define NB_BUILTS 7

# include <struct.h>

int	ft_unset(t_env **lst, char **av, int ac);
int	ft_exit(t_env **lst, char **av, int ac);
int	ft_cd(t_env **lst, char **av, int ac);
int	ft_echo(t_env **lst, char **av, int ac);
int	ft_env(t_env **lst, char **av, int ac);
int	ft_export(t_env **lst, char **av, int ac);
int	ft_pwd(t_env **lst, char **av, int ac);

#endif

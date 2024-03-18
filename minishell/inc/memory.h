/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 19:58:14 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 16:22:00 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <struct.h>

int		ft_free_children(t_child *child);
int		ft_free_ast(t_ast **ast);
int		ft_free_ast_child(t_ast **ast);
int		ft_free_data(t_mini *data);
int		ft_free_token_lst(t_token **token);
int		ft_remove_token_brackets(t_token **token);
int		ft_unlink_tmp_file(t_ast *ast);
t_mini	**ft_memptr_data(t_mini **data);
t_child	**ft_memptr_child(t_child **child);

#endif

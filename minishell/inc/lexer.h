/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:31:19 by diroyer           #+#    #+#             */
/*   Updated: 2022/12/09 02:42:44 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# ifdef BONUS
#  define CHARSET "\n\t |\\$'\"><&()*"
# else
#  define CHARSET "\n\t |\\$'\"><"
# endif

int		lexer(t_token **token, char *input);
void	print_list(t_token *print);
void	ft_tokenadd_back(t_token **first, t_token *new);
void	ft_tokenadd_inside(t_token *current, t_token *new);
t_token	*ft_token_new(void *content, t_type type);
void	free_token(t_token *lst);

#endif

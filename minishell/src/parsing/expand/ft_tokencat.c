/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokencat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 03:35:33 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 08:38:01 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tokencat(t_token **lst)
{
	t_token	*tmp;
	t_token	*current;

	tmp = *lst;
	while (*lst && (*lst)->type == WHITE_SPACE)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		ft_token_delone(tmp);
	}
	current = *lst;
	while (current && current->next)
	{
		while (current && current->next && current->type == WORD
			&& current->next->type == WORD)
			ft_merge_tokens(current, current->next);
		while (current && current->next && current->next->type == WHITE_SPACE)
			ft_remove_token(current, current->next);
		current = current->next;
	}
	return (0);
}

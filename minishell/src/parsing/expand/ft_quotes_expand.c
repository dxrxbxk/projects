/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 02:20:25 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 08:37:01 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_inside_quotes_cat(t_token *lst, t_type quote_type)
{
	t_token	*current;

	lst->type = WORD;
	free(lst->str);
	lst->str = ft_strdup("");
	current = lst->next;
	if (!current)
		return ;
	while (current && current->type != quote_type)
	{
		ft_merge_tokens(lst, current);
		current = lst->next;
	}
	if (current && current->type == quote_type)
		ft_remove_token(lst, current);
}

int	ft_quotes_expand(t_token *lst)
{
	while (lst)
	{
		if (lst->type == QUOTE || lst->type == D_QUOTE)
			ft_inside_quotes_cat(lst, lst->type);
		lst = lst->next;
	}
	return (0);
}

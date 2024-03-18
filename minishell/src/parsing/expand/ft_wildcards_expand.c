/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wilcards_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 06:47:03 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 06:53:32 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_wildcards_expand(t_token *lst)
{
	while (lst)
	{
		if (lst->type == WILDCARDS)
			lst->type = WORD;
		lst = lst->next;
	}
	return (0);
}

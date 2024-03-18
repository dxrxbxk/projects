/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_token_lst.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 04:59:50 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 13:37:54 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_remove_token_brackets(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (*token && (*token)->type == LEFT_P)
	{
		tmp = *token;
		*token = (*token)->next;
		ft_token_delone(tmp);
	}
	tmp = *token;
	while (tmp && tmp->next)
	{
		while (tmp && tmp->next && (tmp->next->type == LEFT_P
				|| tmp->next->type == RIGHT_P))
			ft_remove_token(tmp, tmp->next);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_free_token_lst(t_token **token)
{
	if (!token || !*token)
		return (1);
	free_token(*token);
	*token = NULL;
	return (0);
}

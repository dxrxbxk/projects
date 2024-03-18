/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:32:08 by momadani          #+#    #+#             */
/*   Updated: 2022/12/08 23:53:59 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_state_4(t_token *lst, long separators[2])
{
	ft_move_wspace(&lst, WHITE_SPACE);
	if (lst && lst->type == LEFT_P)
		return (separators[BRACKETS]++, ft_state_4(lst->next, separators));
	if (lst && (lst->type == QUOTE || lst->type == D_QUOTE))
		return (ft_state_1(lst, separators));
	if (lst && ft_token_is_word(lst->type))
		return (ft_state_1(lst->next, separators));
	if (lst && ft_token_is_redir(lst->type))
		return (ft_state_2(lst->next, separators));
	return (ft_checkerror(4, lst, separators));
}

int	ft_state_3(t_token *lst, long separators[2])
{
	ft_move_wspace(&lst, WHITE_SPACE);
	if (lst && ft_token_is_redir(lst->type))
		return (ft_state_2(lst->next, separators));
	if (lst && (lst->type == QUOTE || lst->type == D_QUOTE))
		return (ft_state_1(lst, separators));
	if (lst && ft_token_is_word(lst->type))
		return (ft_state_1(lst->next, separators));
	return (ft_checkerror(3, lst, separators));
}

int	ft_state_2(t_token *lst, long separators[2])
{
	ft_move_wspace(&lst, WHITE_SPACE);
	if (lst && (lst->type == QUOTE || lst->type == D_QUOTE))
		return (ft_state_1(lst, separators));
	if (lst && ft_token_is_word(lst->type))
		return (ft_state_1(lst->next, separators));
	return (ft_checkerror(2, lst, separators));
}

int	ft_state_1(t_token *lst, long separators[2])
{
	if (lst && (lst->type == QUOTE || lst->type == D_QUOTE))
		ft_move_next(&lst, lst->type, &separators[QUOTES]);
	ft_move_wspace(&lst, WHITE_SPACE);
	if (lst && (lst->type == QUOTE || lst->type == D_QUOTE))
		return (ft_state_1(lst, separators));
	if (lst && ft_token_is_word(lst->type))
		return (ft_state_1(lst->next, separators));
	if (lst && ft_token_is_redir(lst->type))
		return (ft_state_2(lst->next, separators));
	if (lst && (lst->type == PIPE))
		return (ft_state_3(lst->next, separators));
	if (lst && (lst->type == AND || lst->type == D_PIPE))
		return (ft_state_4(lst->next, separators));
	if (lst && lst->type == RIGHT_P)
		return (separators[BRACKETS]--, ft_state_5(lst->next, separators));
	return (ft_checkerror(1, lst, separators));
}

int	ft_state_0(t_token *lst, long separators[2])
{
	ft_move_wspace(&lst, WHITE_SPACE);
	if (lst && lst->type == LEFT_P)
		return (separators[BRACKETS]++, ft_state_0(lst->next, separators));
	if (lst && (lst->type == QUOTE || lst->type == D_QUOTE))
		return (ft_state_1(lst, separators));
	if (lst && ft_token_is_word(lst->type))
		return (ft_state_1(lst->next, separators));
	if (lst && ft_token_is_redir(lst->type))
		return (ft_state_2(lst->next, separators));
	return (ft_checkerror(0, lst, separators));
}

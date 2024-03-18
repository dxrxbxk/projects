/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:42:52 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 06:54:39 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_token_delone(t_token *token)
{
	if (token->str)
		free(token->str);
	free(token);
}

void	ft_remove_token(t_token *a, t_token *b)
{
	a->next = b->next;
	ft_token_delone(b);
}

void	ft_merge_tokens(t_token *a, t_token *b)
{
	char	*content;

	if (!a->str)
		content = ft_strdup(b->str);
	else if (!b->str)
		content = a->str;
	else
		content = ft_strjoin(a->str, b->str);
	if (a->str && content != a->str)
		free(a->str);
	a->str = content;
	ft_remove_token(a, b);
}

int	expand(t_token **first, t_env *env)
{
	ft_dollar_expand(*first, env);
	ft_wildcards_expand(*first);
	ft_quotes_expand(*first);
	ft_tokencat(first);
	return (0);
}

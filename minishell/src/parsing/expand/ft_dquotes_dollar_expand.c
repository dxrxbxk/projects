/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dquotes_dollar_expand.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:22:34 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 08:37:41 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_getkey_size_dquotes_expand(char *token)
{
	size_t	size;

	size = 0;
	if (token[size] == '?')
		return (1);
	while (token[size] && (ft_isalnum(token[size]) || token[size] == '_'))
		size++;
	return (size);
}

static char	*ft_extract_key(char **token)
{
	char	*key;
	char	*tmp;
	size_t	size;

	key = NULL;
	if (**token != '?' && **token != '_' && !ft_isalpha(**token))
		return (key);
	size = ft_getkey_size_dquotes_expand(*token);
	key = ft_strndup(*token, size);
	if (!key || !size)
		return (key);
	tmp = *token;
	*token = ft_strdup(*token + size);
	free(tmp);
	return (key);
}

void	ft_dquotes_dollar_expand(t_token *lst, t_env *env)
{
	t_token	*next;
	char	*key;
	char	*value;

	lst->type = WORD;
	next = lst->next;
	if (next == NULL || next->type != WORD)
		return ;
	key = ft_extract_key(&next->str);
	if (!key)
		return ;
	value = ft_extract_env_value(env, key);
	free(key);
	free(lst->str);
	lst->str = value;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usual_dollar_expand.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 19:22:34 by momadani          #+#    #+#             */
/*   Updated: 2022/11/19 22:21:53 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_extract_key(char **token)
{
	char	*key;
	char	*tmp;
	size_t	size;

	key = NULL;
	if (**token != '?' && **token != '_' && !ft_isalpha(**token)
		&& **token != '\'' && **token != '\"')
		return (key);
	size = ft_getkey_size_usual_expand(*token);
	key = ft_strndup(*token, size);
	if (!key || !size)
		return (key);
	tmp = *token;
	*token = ft_strdup(*token + size);
	free(tmp);
	return (key);
}

static int	ft_get_expanded_token_size(char *s)
{
	int	size;

	size = 0;
	if (s[size] == ' ' || s[size] == '\t')
		size = 1;
	else
		while (s[size] && s[size] != ' ' && s[size] != '\t')
			size++;
	return (size);
}

static t_token	*ft_extract_expanded_token(char **value)
{
	char	*content;
	int		size;
	t_type	type;

	size = ft_get_expanded_token_size(*value);
	content = ft_strndup(*value, size);
	if (!content)
		return (NULL);
	type = WORD;
	if (!ft_strcmp(" ", content) || !ft_strcmp("\t", content))
		type = WHITE_SPACE;
	*value += size;
	return (ft_token_new(content, type));
}

static int	ft_add_expanded_token(t_token *current, char *value)
{
	t_token	*new;
	int		size;

	if (!value)
		return (-1);
	size = ft_get_expanded_token_size(value);
	current->str = ft_strndup(value, size);
	if (!current->str)
		return (0);
	current->type = WORD;
	if (!ft_strcmp(" ", current->str) || !ft_strcmp("\t", current->str))
		current->type = WHITE_SPACE;
	new = NULL;
	value += size;
	while (*value)
	{
		new = ft_extract_expanded_token(&value);
		if (!new)
			return (0);
		ft_tokenadd_inside(current, new);
		current = current->next;
	}
	return (1);
}

void	ft_usual_dollar_expand(t_token *lst, t_env *env)
{
	t_token	*next;
	char	*key;
	char	*value;

	lst->type = WORD;
	next = lst->next;
	if (next == NULL || (next->type != WORD && next->type != QUOTE
			&& next->type != D_QUOTE))
		return ;
	key = ft_extract_key(&next->str);
	if (!key)
		return ;
	value = ft_extract_env_value(env, key);
	free(key);
	if (!*next->str)
		ft_remove_token(lst, next);
	free(lst->str);
	lst->str = value;
	if (value)
	{
		ft_add_expanded_token(lst, value);
		free(value);
	}
}

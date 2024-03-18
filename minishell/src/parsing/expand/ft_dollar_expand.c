/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:42:52 by momadani          #+#    #+#             */
/*   Updated: 2022/11/19 22:18:48 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_skip_heredoc_delimiter_expand(t_token *lst, t_env *env,
						void (*ft_heredoc_delimiter_expand)(t_token *, t_env *))
{
	int	inside_quotes;

	while (lst && lst->type == WHITE_SPACE)
		lst = lst->next;
	inside_quotes = 0;
	while (lst && (lst->type != WHITE_SPACE || inside_quotes))
	{
		if (lst->type == QUOTE && !inside_quotes)
			inside_quotes = 1;
		else if (lst->type == D_QUOTE && !inside_quotes)
			inside_quotes = 2;
		else if (lst->type == QUOTE && inside_quotes == 1)
			inside_quotes = 0;
		else if (lst->type == D_QUOTE && inside_quotes == 2)
			inside_quotes = 0;
		else if (lst->type == DOLLAR)
			(*ft_heredoc_delimiter_expand)(lst, env);
		lst = lst->next;
	}
}

char	*ft_extract_env_value(t_env *env, char *key)
{
	if (*key == '?')
		return (ft_itoa(g_status));
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

size_t	ft_getkey_size_usual_expand(char *token)
{
	size_t	size;

	size = 0;
	if (token[size] == '\'' || token[size] == '"')
		return (size);
	if (*token == '?')
		return (1);
	while (token[size] && (ft_isalnum(token[size]) || token[size] == '_'))
		size++;
	return (size);
}

void	ft_change_dollar_expand(void (**ft)(t_token *, t_env *), t_token *lst)
{
	static int	quotes;

	if (!quotes && lst->type == QUOTE)
	{
		quotes = 1;
		*ft = &ft_squotes_dollar_expand;
	}
	else if (!quotes && lst->type == D_QUOTE)
	{
		quotes = 2;
		*ft = &ft_dquotes_dollar_expand;
	}
	else if (quotes == 1 && lst->type == QUOTE)
	{
		quotes = 0;
		*ft = &ft_usual_dollar_expand;
	}
	else if (quotes == 2 && lst->type == D_QUOTE)
	{
		quotes = 0;
		*ft = &ft_usual_dollar_expand;
	}
}

int	ft_dollar_expand(t_token *lst, t_env *env)
{
	void	(*ft_current_dollar_expand)(t_token *, t_env *);

	ft_current_dollar_expand = &ft_usual_dollar_expand;
	while (lst)
	{
		if (lst->type == D_LESS)
			ft_skip_heredoc_delimiter_expand(lst->next, env,
				&ft_squotes_dollar_expand);
		else if (lst->type == D_QUOTE || lst->type == QUOTE)
			ft_change_dollar_expand(&ft_current_dollar_expand, lst);
		else if (lst->type == DOLLAR)
			(*ft_current_dollar_expand)(lst, env);
		lst = lst->next;
	}
	return (0);
}

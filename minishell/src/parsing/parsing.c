/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 19:39:02 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 18:22:56 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parsing(char *input, t_token **first, t_ast **root, t_env *env)
{
	if (lexer(first, input) == -1)
		return (free(input), ft_free_token_lst(first), -1);
	if (parser(*first) == -1)
		return (free(input), ft_free_token_lst(first), -1);
	if (expand(first, env) == -1)
		return (free(input), ft_free_token_lst(first), -1);
	if (!*first)
		return (1);
	if (ast_init(root, *first) == -1)
		return (ft_remove_token_brackets(first), ft_free_ast(root), -1);
	ft_remove_token_brackets(first);
	return (0);
}

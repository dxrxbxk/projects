/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 23:46:00 by momadani          #+#    #+#             */
/*   Updated: 2022/11/16 23:46:15 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	ft_rbranch_len_skip_null(t_ast *ast)
{
	size_t	len;

	len = 0;
	while (ast)
	{
		if (ast->token->str)
			len++;
		ast = ast->right;
	}
	return (len);
}

size_t	ft_lbranch_len(t_ast *ast)
{
	size_t	len;

	len = 0;
	while (ast)
	{
		len++;
		ast = ast->left;
	}
	return (len);
}

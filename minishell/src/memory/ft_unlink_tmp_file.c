/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unlink_tmp_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:15:08 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 16:15:43 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_unlink_tmp_file(t_ast *ast)
{
	while (ast && ast->left)
	{
		if (ast->token->type == D_LESS)
		{
			if (unlink(ast->left->token->str) == -1)
				ft_error("unlink: ", strerror(errno), NULL, -1);
			break ;
		}
		ast = ast->left;
	}
	return (ast != NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:42:28 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 08:33:46 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_init_cmd_node(t_ast *ast, t_token **token)
{
	ft_create_node_right(&ast, CMD);
	ft_addcmd_node(ast->right, token);
	return (0);
}

int	ft_create_tree(t_ast *ast, t_token **token)
{
	while (*token)
	{
		if (*token && (*token)->type == LEFT_P)
		{
			ft_create_node_right(&ast, OP_SEQ);
			*token = (*token)->next;
			ft_create_tree(ast->right, token);
		}
		if (*token && (ft_token_is_word((*token)->type)
				|| ft_token_is_redir((*token)->type)))
			ft_init_cmd_node(ast, token);
		if (*token && (*token)->type == RIGHT_P)
		{
			*token = (*token)->next;
			break ;
		}
		if (*token && ((*token)->type == AND || (*token)->type == D_PIPE))
		{
			ft_astadd_last_left(&ast, ft_astnew(*token));
			ft_create_node_left(&ast, OP_SEQ);
			*token = (*token)->next;
			ast = ast->left->left;
		}
	}
	return (0);
}

int	ast_init(t_ast **root, t_token *token)
{
	if (ft_create_node_right(root, OP_SEQ) == -1)
		return (-1);
	return (ft_create_tree(*root, &token));
}

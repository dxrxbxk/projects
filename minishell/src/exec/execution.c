/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 22:41:05 by momadani          #+#    #+#             */
/*   Updated: 2022/11/20 16:49:31 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	launch_children(t_ast *root, t_ast *ast, t_mini *data)
{
	(void)root;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (ast->token->type == PIPE_SEQ)
		return (launch_pipe_sequence(ast->left, data));
	else if (ast->token->type == CMD)
		return (launch_child(ast, data));
	return (1);
}

int	execution(t_ast *root, t_ast *ast, t_mini *data)
{
	if (!ast)
		return (0);
	if (ast->token->type == OP_SEQ)
	{
		if (execution(root, ast->right, data) == -1)
			return (-1);
		if (execution(root, ast->left, data) == -1)
			return (-1);
	}
	else if (ast->token->type == CMD || ast->token->type == PIPE_SEQ)
		return (launch_children(root, ast, data));
	else if (ast->token->type == AND && g_status == 0)
		return (execution(root, ast->left, data));
	else if (ast->token->type == D_PIPE && g_status != 0)
		return (execution(root, ast->left, data));
	else
		return (execution(root, ast->left->left, data));
	return (0);
}

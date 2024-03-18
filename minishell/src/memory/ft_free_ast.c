/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 23:55:37 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 16:15:33 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_free_ast_node(t_ast **ast)
{
	if (!ast || !*ast)
		return (1);
	if ((*ast)->token)
	{
		ft_token_delone((*ast)->token);
		(*ast)->token = NULL;
	}
	(*ast)->left = NULL;
	(*ast)->right = NULL;
	free(*ast);
	*ast = NULL;
	return (0);
}

int	ft_free_cmd_args_branch(t_ast **ast)
{
	if (!ast || !*ast)
		return (0);
	ft_free_cmd_args_branch(&(*ast)->right);
	ft_free_ast_node(ast);
	return (0);
}

int	ft_free_cmd_redir_branch(t_ast **ast)
{
	if (!ast || !*ast)
		return (0);
	ft_free_cmd_redir_branch(&(*ast)->left);
	ft_free_ast_node(ast);
	return (0);
}

int	ft_free_pipe_seq(t_ast **ast)
{
	if (!ast || !*ast)
		return (0);
	if ((*ast)->token->type == OP_SEQ || (*ast)->token->type == PIPE_SEQ
		|| (*ast)->token->type == PIPE)
	{
		ft_free_pipe_seq(&(*ast)->left);
		ft_free_pipe_seq(&(*ast)->right);
	}
	else if ((*ast)->token->type == CMD)
	{
		ft_unlink_tmp_file((*ast)->left);
		ft_free_cmd_redir_branch(&(*ast)->left);
		ft_free_cmd_args_branch(&(*ast)->right);
	}
	ft_free_ast_node(ast);
	return (0);
}

int	ft_free_ast(t_ast **ast)
{
	if (!ast || !*ast)
		return (0);
	if ((*ast)->token->type == OP_SEQ
		|| (*ast)->token->type == AND || (*ast)->token->type == D_PIPE)
	{
		ft_free_ast(&(*ast)->left);
		ft_free_ast(&(*ast)->right);
	}
	else if ((*ast)->token->type == CMD)
	{
		ft_unlink_tmp_file((*ast)->left);
		ft_free_cmd_redir_branch(&(*ast)->left);
		ft_free_cmd_args_branch(&(*ast)->right);
		ft_free_ast_node(ast);
	}
	else if ((*ast)->token->type == PIPE_SEQ)
		ft_free_pipe_seq(ast);
	ft_free_ast_node(ast);
	return (0);
}

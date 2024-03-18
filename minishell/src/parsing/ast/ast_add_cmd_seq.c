/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add_cmd_seq.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 08:11:01 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 08:13:08 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_add_full_cmd(t_ast *ast, t_token **token)
{
	while (*token && (*token)->type != D_PIPE && (*token)->type != AND
		&& (*token)->type != RIGHT_P && (*token)->type != PIPE)
	{
		if (ft_token_is_redir((*token)->type))
		{
			if (ft_astadd_last_left(&ast, ft_astnew(*token)) == -1)
				return (-1);
			if (ft_astadd_last_left(&ast, ft_astnew((*token)->next)) == -1)
				return (-1);
			*token = (*token)->next->next;
		}
		else if ((*token)->type == WORD)
		{
			if (ft_astadd_last_right(&ast, ft_astnew(*token)) == -1)
				return (-1);
			*token = (*token)->next;
		}	
		else
			*token = (*token)->next;
	}
	return (0);
}

int	ft_is_pipe_seq(t_token *token)
{
	while (token && token->type != D_PIPE && token->type != AND
		&& token->type != RIGHT_P && token->type != PIPE)
		token = token->next;
	return (token && token->type == PIPE);
}

int	ft_add_pipe_sequence(t_ast *ast, t_token *token)
{
	ast->token->type = PIPE_SEQ;
	while (ft_is_pipe_seq(token))
	{
		if (ft_create_node_left(&ast, OP_SEQ) == -1)
			return (-1);
		ast = ast->left;
		if (ft_create_node_right(&ast, CMD) == -1)
			return (-1);
		if (ft_add_full_cmd(ast->right, &token) == -1)
			return (-1);
		if (ft_astadd_last_left(&ast, ft_astnew(token)) == -1)
			return (-1);
		token = token->next;
		ast = ast->left;
	}
	if (ft_create_node_left(&ast, OP_SEQ) == -1)
		return (-1);
	ast = ast->left;
	if (ft_create_node_right(&ast, CMD) == -1)
		return (-1);
	if (ft_add_full_cmd(ast->right, &token) == -1)
		return (-1);
	return (0);
}

int	ft_addcmd_node(t_ast *ast, t_token **token)
{
	int	ret_val;

	ret_val = 0;
	if (ft_is_pipe_seq(*token))
		ret_val = ft_add_pipe_sequence(ast, *token);
	else
		ret_val = ft_add_full_cmd(ast, token);
	while (*token && (*token)->type != D_PIPE && (*token)->type != AND
		&& (*token)->type != RIGHT_P)
		*token = (*token)->next;
	return (ret_val);
}

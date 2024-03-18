/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 22:41:05 by momadani          #+#    #+#             */
/*   Updated: 2022/11/23 02:09:20 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_heredoc(t_ast *ast)
{
	while (ast && ast->token->type != D_LESS)
		ast = ast->left;
	return (ast != NULL);
}

static int	set_cmd_heredoc(t_ast *ast, t_mini *data)
{
	char	*file_path;
	char	*delim;

	if (!ast || !is_heredoc(ast->left))
		return (0);
	file_path = heredoc_path();
	while (ast)
	{
		if (ast->token->type == D_LESS && ast->left)
		{
			delim = ft_strdup(ast->left->token->str);
			if (!delim)
				return (-1);
			free(ast->left->token->str);
			ast->left->token->str = ft_strdup(file_path);
			if (manage_heredoc_child(file_path, delim, data) == -1)
				return (-1);
			free(delim);
		}
		ast = ast->left;
	}
	free(file_path);
	return (0);
}

static int	set_pipe_seq_heredoc(t_ast *ast, t_mini *data)
{
	while (ast)
	{
		if (set_cmd_heredoc(ast->right, data) == -1)
			return (-1);
		ast = ast->left;
		if (ast)
			ast = ast->left;
	}
	return (0);
}

int	set_heredoc_files(t_ast *ast, t_mini *data)
{
	if (!ast)
		return (0);
	if (ast->token->type == OP_SEQ)
	{
		if (set_heredoc_files(ast->right, data) == -1)
			return (-1);
		if (set_heredoc_files(ast->left, data) == -1)
			return (-1);
	}
	else if (ast->token->type == CMD)
		return (set_cmd_heredoc(ast, data));
	else if (ast->token->type == PIPE_SEQ)
		return (set_pipe_seq_heredoc(ast->left, data));
	else if (ast->token->type == AND || ast->token->type == D_PIPE)
		return (set_heredoc_files(ast->left, data));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 03:20:31 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 08:41:14 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_get_cmd_redirections_pipeseq(t_child *child, t_ast *ast)
{
	size_t	len;
	size_t	i;

	len = 1;
	len += ft_lbranch_len(ast);
	if (child->prev && child->next)
		len++;
	child->redir = malloc(sizeof(t_redir) * (len + 1));
	if (!child->redir)
		return (ft_error(MEM_ERROR, NULL, NULL, -1));
	i = 0;
	if (child->prev)
		ft_fill_redir_struct(&child->redir[i++], PIPE_IN, NULL, -1);
	if (child->next)
		ft_fill_redir_struct(&child->redir[i++], PIPE_OUT, NULL, -1);
	if (ft_add_cmd_redirections(child->redir + i, ast) == -1)
		return (-1);
	return (0);
}

int	ft_init_pipe_child_redirections(t_child *child, t_ast *ast)
{
	while (child)
	{
		if (ast && ast->right)
			if (ft_get_cmd_redirections_pipeseq(child, ast->right->left) == -1)
				return (-1);
		ast = ast->left;
		if (ast)
			ast = ast->left;
		child = child->next;
	}
	return (0);
}

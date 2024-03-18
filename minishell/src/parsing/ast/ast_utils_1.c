/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:17:04 by momadani          #+#    #+#             */
/*   Updated: 2022/12/08 23:54:36 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_astadd_last_left(t_ast **root, t_ast *elem)
{
	t_ast	*current;

	current = *root;
	if (!elem)
		return (-1);
	if (!*root)
		*root = elem;
	else
	{
		while (current->left)
			current = current->left;
		current->left = elem;
	}
	return (0);
}

int	ft_astadd_last_right(t_ast **root, t_ast *elem)
{
	t_ast	*current;

	current = *root;
	if (!elem)
		return (-1);
	if (!*root)
		*root = elem;
	else
	{
		while (current->right)
			current = current->right;
		current->right = elem;
	}
	return (0);
}

int	ft_create_node_left(t_ast **root, t_type type)
{
	t_token	*new_tok;
	t_ast	*new_ast;

	new_tok = ft_token_new(NULL, type);
	if (!new_tok)
		return (-1);
	new_ast = ft_astnew(new_tok);
	if (!new_ast)
		return (-1);
	ft_astadd_last_left(root, new_ast);
	return (0);
}

int	ft_create_node_right(t_ast **root, t_type type)
{
	t_token	*new_tok;
	t_ast	*new_ast;

	new_tok = ft_token_new(NULL, type);
	if (!new_tok)
		return (-1);
	new_ast = ft_astnew(new_tok);
	if (!new_ast)
		return (-1);
	ft_astadd_last_right(root, new_ast);
	return (0);
}

t_ast	*ft_astnew(t_token *token)
{
	t_ast	*new;

	if (!token)
		return (NULL);
	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->token = token;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

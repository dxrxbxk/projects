/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 21:10:15 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/21 05:01:31 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *lst)
{
	t_token	*tmp;

	tmp = NULL;
	while (lst)
	{
		tmp = lst->next;
		ft_token_delone(lst);
		lst = tmp;
	}
}

void	print_list(t_token *print)
{
	while (print)
	{
		printf("tok->str = \"%s\" and tok->type = %d\n", print->str, print->type);
		print = print->next;
	}
}

void	ft_tokenadd_back(t_token **first, t_token *new)
{
	t_token	*current;

	current = *first;
	if (!*first)
		*first = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void	ft_tokenadd_inside(t_token *current, t_token *new)
{
	t_token	*next;

	if (!current)
		return ;
	next = current->next;
	current->next = new;
	new->next = next;
}

t_token	*ft_token_new(void *content, t_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = content;
	new->type = type;
	new->next = NULL;
	return (new);
}

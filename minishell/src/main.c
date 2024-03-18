/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:53:22 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/23 19:24:47 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <prompt.h>

int	g_status = 0;

void	ft_reset_vars(char **input, t_token **token,
				t_ast **root, t_child **ptr)
{
	*input = NULL;
	*token = NULL;
	*root = NULL;
	*ptr = NULL;
}

int	prompt(t_mini *data)
{
	char	*input;
	t_token	*tok;
	t_ast	*root;
	t_child	*ptr;

	data->root = &root;
	ft_memptr_data(&data);
	while (1)
	{
		handle_signals();
		data = get_env_path(data->env, data);
		ft_reset_vars(&input, &tok, &root, &ptr);
		ft_memptr_child(&ptr);
		input = get_input(g_status, data->env);
		if (input == NULL)
			ft_exit(&data->env, NULL, 0);
		if (parsing(input, &tok, &root, data->env) != 0)
			continue ;
		free(input);
		if (set_heredoc_files(root, data) == -1)
			continue ;
		execution(root, root, data);
		ft_free_ast(&root);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_mini	data;

	(void)av;
	if (ac != 1)
		return (0);
	if (!env || !*env)
		env = create_env();
	get_env(&data, env);
	get_path(&data, env);
	get_shlvl(&data);
	if (prompt(&data) == -1)
		return (0);
	return (0);
}

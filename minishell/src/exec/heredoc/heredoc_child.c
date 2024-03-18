/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:51:06 by momadani          #+#    #+#             */
/*   Updated: 2022/11/21 16:03:30 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_sigint_heredoc(int signal)
{
	t_mini	**data;

	(void)signal;
	data = ft_memptr_data(NULL);
	ft_free_ast_child((*data)->root);
	ft_free_data(*data);
	exit(130);
}

void	exec_heredoc_child(char *file_path, char *delim, t_mini *data)
{
	int	ret;

	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	ret = apply_heredoc(file_path, delim);
	free(file_path);
	free(delim);
	ft_free_ast_child(data->root);
	ft_free_data(data);
	if (ret == -1)
		exit(1);
	exit(0);
}

int	manage_heredoc_child(char *file_path, char *delim, t_mini *data)
{
	pid_t	pid;
	int		child_status;
	int		exit_status;

	exit_status = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (ft_error("fork: ", strerror(errno), NULL, -1));
	if (pid == 0)
		exec_heredoc_child(file_path, delim, data);
	waitpid(pid, &child_status, 0);
	if (WIFEXITED(child_status) && WEXITSTATUS(child_status) == 130)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		exit_status = 130;
		g_status = exit_status;
	}
	signal(SIGINT, inthandler);
	signal(SIGQUIT, SIG_IGN);
	if (exit_status == 130)
		return (free(delim), free(file_path), ft_free_ast(data->root), -1);
	return (0);
}

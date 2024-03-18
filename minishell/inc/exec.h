/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:46:34 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/23 02:46:14 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/types.h>
# include <sys/wait.h>
# include <struct.h>

char			*heredoc_path(void);
int				apply_heredoc(char *path, char *delim);
int				manage_heredoc_child(char *file_path,
					char *delim, t_mini *data);
int				set_heredoc_files(t_ast *ast, t_mini *data);
int				set_heredoc(t_ast *ast);

int				ft_open(char *path, t_redir_type type);
int				ft_dup2(int fd, t_redir_type type);
int				ft_close(int *fd);
t_redir_type	ft_which_redir(t_type type);
void			ft_fill_redir_struct(t_redir *redir,
					t_redir_type type, char *path, int fd);

void			ft_exit_free(t_mini *data, t_child *child, int retval);
int				ft_quit_free_builtin(t_child *child);
int				set_child_status(t_child *child, int exit_status);

int				launch_child( t_ast *ast, t_mini *data);
void			exec_child(t_child *child, t_ast *ast, t_mini *data);

int				launch_pipe_sequence(t_ast *ast, t_mini *data);
void			exec_pipe_child(t_child *child, t_ast *ast, t_mini *data);
int				ft_init_pipe_child_redirections(t_child *child, t_ast *ast);
int				ft_create_pipe(t_child *child);
int				ft_close_pipe(t_child *child);
int				ft_get_pipein_redir_rank(t_redir *redir);
int				ft_get_pipeout_redir_rank(t_redir *redir);

int				launch_builtin(t_child *child, t_ast *ast, t_mini *data);
int				exec_builtin(t_child *child, t_ast *ast, t_mini *shell);
int				ft_save_main_fds(int fds[2], t_child *child);
int				ft_restore_main_fds(int fds[2], t_child *child);
int				is_builtin(t_ast *ast);
t_built			*init_fpointer(void);

int				execution(t_ast *root, t_ast *ast, t_mini *data);

void			ft_child_add_back(t_child **child, t_child *elem);
t_child			*ft_child_new(void);

int				ft_wait_children(t_child *first);
int				ft_interpret_child_status(t_child *child);
int				ft_is_sigint(int status);

int				ft_check_is_directory(t_mini *data, t_child *child, char *path);
int				ft_get_args(t_child *child, t_ast *ast);

void			ft_fill_redir_struct(t_redir *redir, t_redir_type type,
					char *path, int fd);
t_redir_type	ft_which_redir(t_type type);
int				ft_apply_redirections(t_redir *redir, t_child *child);
int				ft_add_cmd_redirections(t_redir *redir, t_ast *ast);
int				ft_get_cmd_redirections(t_child *child, t_ast *ast);
int				ft_get_cmd_redirections_pipeseq(t_child *child, t_ast *ast);

int				ft_find_cmd_path(t_child *child, t_mini *data);

#endif

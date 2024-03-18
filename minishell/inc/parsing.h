/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:32:09 by diroyer           #+#    #+#             */
/*   Updated: 2022/12/08 23:44:37 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <minishell.h>

# define SYNTAX_ERROR "syntax error near unexpected token `" 
# define END_QUOTE "\'"
# define BRACKETS 0
# define QUOTES 1

int		parsing(char *input, t_token **first, t_ast **root, t_env *env);

int		ast_init(t_ast **root, t_token *token);
int		ft_addcmd_node(t_ast *ast, t_token **token);
int		ft_addpipe_sequence(t_ast *ast, t_token *token);
int		ft_is_pipe_seq(t_token *token);
int		ft_add_full_cmd(t_ast *ast, t_token **token);

int		ft_astadd_last_left(t_ast **root, t_ast *elem);
int		ft_astadd_last_right(t_ast **root, t_ast *elem);
int		ft_create_node_left(t_ast **root, t_type type);
int		ft_create_node_right(t_ast **root, t_type type);
t_ast	*ft_astnew(t_token *token);
size_t	ft_lbranch_len(t_ast *ast);
size_t	ft_rbranch_len_skip_null(t_ast *ast);

void	ft_token_delone(t_token *token);
void	ft_remove_token(t_token *a, t_token *b);
void	ft_merge_tokens(t_token *a, t_token *b);
int		expand(t_token **first, t_env *env);

void	ft_squotes_dollar_expand(t_token *lst, t_env *env);

void	ft_usual_dollar_expand(t_token *lst, t_env *env);

int		ft_quotes_expand(t_token *lst);

int		ft_wildcards_expand(t_token *lst);

void	ft_parserror(char *msg);
int		ft_checkerror(int state, t_token *lst, long separators[2]);
int		ft_state_5(t_token *lst, long separators[2]);
int		ft_state_4(t_token *lst, long separators[2]);
int		ft_state_3(t_token *lst, long separators[2]);
int		ft_state_2(t_token *lst, long separators[2]);
int		ft_state_1(t_token *lst, long separators[2]);
int		ft_state_0(t_token *lst, long separators[2]);

int		ft_token_is_word(t_type type);
int		ft_token_is_redir(t_type type);
int		ft_move_wspace(t_token **lst, t_type type);
int		ft_move_next(t_token **lst, t_type type, long *separator);
int		parser(t_token *first);

void	ft_dquotes_dollar_expand(t_token *lst, t_env *env);

int		ft_tokencat(t_token **lst);

void	ft_skip_heredoc_delimiter_expand(t_token *lst, t_env *env,
			void (*ft_heredoc_delimiter_expand)(t_token *, t_env *));
char	*ft_extract_env_value(t_env *env, char *key);
size_t	ft_getkey_size_usual_expand(char *token);
void	ft_change_dollar_expand(void (**ft)(t_token *, t_env *), t_token *lst);
int		ft_dollar_expand(t_token *lst, t_env *env);

#endif

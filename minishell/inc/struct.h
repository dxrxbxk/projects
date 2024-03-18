/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:46:24 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/21 21:30:04 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <fcntl.h>

typedef enum e_type
{
	WORD,
	WHITE_SPACE,
	NLINE,
	PIPE,
	D_PIPE,
	DOLLAR,
	QUOTE,
	D_QUOTE,
	GREAT,
	D_GREAT,
	LESS,
	D_LESS,
	AND,
	LEFT_P,
	RIGHT_P,
	WILDCARDS,
	OP_SEQ,
	PIPE_SEQ,
	CMD,
}				t_type;

typedef enum e_redir_type
{
	INFILE,
	HEREDOC,
	OUTFILE,
	APPEND,
	PIPE_IN,
	PIPE_OUT,
	END,
}				t_redir_type;

typedef struct s_ast
{
	struct s_token	*token;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

typedef struct s_token
{
	char			*str;
	t_type			type;
	struct s_token	*next;
}				t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_built
{
	char	*cmd;
	int		(*builtins)(t_env **, char **, int);
}				t_built;

typedef struct s_redir
{
	t_redir_type	type;
	char			*path;
	int				fd;
}				t_redir;

typedef struct s_child
{
	char				*pathname;
	char				**argv;
	char				**envp;
	t_redir				*redir;
	int					status;
	pid_t				pid;
	struct s_child		*prev;
	struct s_child		*next;
}				t_child;

typedef struct s_mini
{
	char	*path;
	char	**spath;
	t_ast	**root;
	t_env	*env;
	t_built	*built;
}				t_mini;

#endif

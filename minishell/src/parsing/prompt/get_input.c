/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:34:28 by diroyer           #+#    #+#             */
/*   Updated: 2023/02/23 18:27:12 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <prompt.h>
#include <termios.h>

static char	*get_user_id(t_env *lst)
{
	char	*user;
	char	*user_color;

	if (!get_env_key(lst, "USER"))
		user = "not found";
	else
		user = get_key_value(lst, "USER");
	user_color = ft_mega_join(SHELL, user, "@\033[0m");
	return (user_color);
}

static char	*ret_pwd_color(void)
{
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	tmp = cwd;
	cwd = ft_mega_join(PWD_COLOR, ft_strrchr(cwd, '/') + 1, "\033[0m ");
	free(tmp);
	return (cwd);
}

static char	*get_prompt(int ret, t_env *lst)
{
	char	*prompt;
	char	*pwd;
	char	*arrow;
	char	*user;

	if (THEME == 0)
		return (ft_strdup("minish-1.0$ "));
	if (ret == 0)
		arrow = GREEN_ARROW;
	else
		arrow = RED_ARROW;
	pwd = ret_pwd_color();
	user = get_user_id(lst);
	prompt = ft_mega_join(arrow, user, pwd);
	free(pwd);
	free(user);
	return (prompt);
}

char	*get_input(int ret, t_env *env)
{
	char	*input;
	char	*prompt;

	if (!isatty(0))
	{
		input = get_next_line(0);
		if (input && input[ft_strlen(input) - 1] == '\n')
			input[ft_strlen(input) - 1] = '\0';
	}
	else
	{
		if (!isatty(2))
			input = readline("");
		else
		{
			prompt = get_prompt(ret, env);
			input = readline(prompt);
			free(prompt);
		}
		if (input)
			add_history(input);
	}
	return (input);
}

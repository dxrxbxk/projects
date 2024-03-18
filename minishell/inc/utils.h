/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:36:48 by diroyer           #+#    #+#             */
/*   Updated: 2023/02/10 04:57:18 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <struct.h>
# include <string.h>

int		ft_putstr_fdr(char *s, int fd);
void	free_tab(char ***tab);
char	*ft_strlastchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_error(char *msg, char *var, char *msg2, int ret);
char	*get_next_line(int fd);
char	*ft_mega_join(char *s1, char *s2, char *s3);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	**ft_lst_to_tab(t_env *lst);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int nb);
int		ft_words_count(char const *s, char c);
char	*ft_strndup(const char *s1, int len);
void	ft_putendl_fd(char *s, int fd);
void	ft_swap_str(char **a, char **b);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isdigit(int c);
int		ft_findi(char *str, char find);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
void	ft_putchar_fd(char c, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
size_t	ft_strlcat(char *dst, char const *src, size_t size);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	ft_strcpy(char *dst, const char *src);
void	ft_strcat(char *dst, char const *src);

#endif

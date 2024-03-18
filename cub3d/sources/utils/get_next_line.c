/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 21:21:43 by momadani          #+#    #+#             */
/*   Updated: 2023/03/20 03:29:18 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static char	*ft_free_str(char *save)
{
	if (save)
		free(save);
	return (NULL);
}

static void	ft_reload_buffer(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[j] && str[j] != '\n')
		j++;
	if (str[j] == '\n')
	{
		while (str[j++])
			str[i++] = str[j];
		while (str[i])
			str[i++] = '\0';
	}
	else
		while (str[i])
			str[i++] = '\0';
}

static char	*ft_put_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (ft_free_str(str));
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\n';
	line[i + 1] = '\0';
	ft_free_str(str);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[1024][BUFFER_SIZE + 1];
	int			bytes;
	char		*line;

	bytes = 1;
	line = NULL;
	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, "", 0) == -1)
		return (ft_free_str(line));
	line = ft_strjoin(line, buffer[fd]);
	if (!line)
		return (NULL);
	while (bytes > 0 && !ft_strchr(line, '\n'))
	{
		bytes = read(fd, buffer[fd], BUFFER_SIZE);
		if (bytes == -1)
			break ;
		buffer[fd][bytes] = '\0';
		line = ft_strjoin(line, buffer[fd]);
	}
	if (bytes < 0 || !line || !*line)
		return (ft_free_str(line));
	if (*line)
		line = ft_put_line(line);
	ft_reload_buffer(buffer[fd]);
	return (line);
}

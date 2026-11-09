/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutalay <mutalay@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 14:43:48 by mutalay           #+#    #+#             */
/*   Updated: 2026/11/09 21:10:31 by mutalay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	read_until_newline(char **stored, int fd, char *buf)
{
	char	*tmp;
	ssize_t	num_read;

	num_read = 1;
	while (!ft_strchr(*stored, '\n') && num_read > 0)
	{
		num_read = read(fd, buf, BUFFER_SIZE);
		if (num_read == -1)
		{
			free(*stored);
			*stored = NULL;
			return ;
		}
		buf[num_read] = '\0';
		tmp = ft_strjoin(*stored, buf);
		free(*stored);
		*stored = tmp;
	}
}

static void	fill_stored(char **stored, int fd)
{
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return ;
	if (!*stored)
	{
		*stored = ft_strdup("");
		if (!*stored)
		{
			free(buf);
			return ;
		}
	}
	read_until_newline(&*stored, fd, buf);
	free(buf);
}

static char	*split_stored(char **stored)
{
	char		*line;
	char		*tmp;
	char		*next_line;

	line = NULL;
	next_line = ft_strchr(*stored, '\n');
	if (next_line)
	{
		line = ft_substr(*stored, 0, (next_line - *stored) + 1);
		tmp = ft_strdup(next_line +1);
		free(*stored);
		*stored = tmp;
		return (line);
	}
	if (*stored && **stored != '\0')
	{
		line = *stored;
		*stored = NULL;
		return (line);
	}
	free(*stored);
	*stored = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*stored[FD_SIZE];

	if (fd < 0 || fd >= FD_SIZE || BUFFER_SIZE <= 0)
		return (NULL);
	fill_stored(&stored[fd], fd);
	if (!stored[fd])
		return (NULL);
	return (split_stored(&stored[fd]));
}

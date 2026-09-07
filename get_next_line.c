/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutalay <mutalay@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 14:43:48 by mutalay           #+#    #+#             */
/*   Updated: 2026/09/07 19:36:01 by mutalay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	fill_stored(char **stored, int fd)
{
	char	*buf;
	char	*tmp;
	ssize_t	numread;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return ;
	numread = 1;
	if (!*stored)
		*stored = ft_strdup("");
	while (!ft_strchr(*stored, '\n') && numread > 0)
	{
		numread = read(fd, buf, BUFFER_SIZE);
		if (numread == -1)
		{
			free(buf);
			return ;
		}
		buf[numread] = '\0';
		tmp = ft_strjoin(*stored, buf);
		free(*stored);
		*stored = tmp;
	}
	free(buf);
}

char	*line_and_newstored(char **stored)
{
	char		*line;
	char		*tmp;
	char		*next_stop;

	line = NULL;
	next_stop = ft_strchr(*stored, '\n');
	if (next_stop)
	{
		line = ft_substr(*stored, 0, (next_stop - *stored) + 1);
		tmp = ft_strdup(next_stop +1);
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
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*stored;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fill_stored(&stored, fd);
	if (!stored)
		return (NULL);
	return (line_and_newstored(&stored));
}

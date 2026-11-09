/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutalay <mutalay@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 16:46:18 by mutalay           #+#    #+#             */
/*   Updated: 2026/11/09 19:17:42 by mutalay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*news;

	i = 0;
	news = (char *)malloc(ft_strlen(s) + 1);
	if (!news)
		return (NULL);
	while (s[i])
	{
		news[i] = s[i];
		i++;
	}
	news[i] = 0;
	return (news);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ch;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			ch = (char *)&s[i];
			return (ch);
		}
		i++;
	}
	if ((char)c == '\0')
	{
		ch = (char *)&s[i];
		return (ch);
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*news;
	size_t	size;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		return (malloc(1));
	}
	size = ft_strlen(s) - start;
	if (len < size)
		size = len;
	news = (char *)malloc(size + 1);
	if (!news)
		return (NULL);
	i = 0;
	while (i < size && s[start + i] != '\0')
	{
		news[i] = s[start + i];
		i++;
	}
	news[i] = '\0';
	return (news);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*news;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	news = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!news)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		news[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		news[i + j] = s2[j];
		j++;
	}
	news[i + j] = '\0';
	return (news);
}

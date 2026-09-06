/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutalay <mutalay@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 16:46:18 by mutalay           #+#    #+#             */
/*   Updated: 2026/09/03 18:00:48 by mutalay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*storage;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > (__SIZE_MAX__ / size))
		return (NULL);
	storage = malloc(nmemb * size);
	if (storage == NULL)
		return (NULL);
	ft_bzero(storage, nmemb * size);
	return (storage);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
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

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		return (ft_calloc(1, 1));
	}
	size = ft_strlen(s) - start;
	if (len < size)
	{
		size = len;
	}
	news = (char *)malloc(size + 1);
	if (!news)
		return (NULL);
	ft_strlcpy(news, &s[start], size + 1);
	return (news);
}

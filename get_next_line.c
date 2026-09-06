/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mutalay <mutalay@student.42istanbul.com.tr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 15:30:32 by mutalay           #+#    #+#             */
/*   Updated: 2026/09/06 12:15:22 by mutalay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*stop_new_line(char *stored, int fd)
{
	
}

char	*get_next_line(int fd)
{
	char *line;
	static char *stored;
	if (fd == -1 || BUFFER_SIZE <= 0)
		return (0);
		
	return 0;
}

int	main(int argc, char *argv[])
{
	int fd = open(argv[1], O_RDONLY);

	char *line = get_next_line(fd);
	

	printf("fd -> %d\n",fd);
	printf("line -> %s\n",line);

	close(fd);
	return 0;
	
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:18:11 by gustavo-lin       #+#    #+#             */
/*   Updated: 2024/12/17 16:40:33 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

// int shift_buffer()
// {}

// o array e verifica se existe um caractere \n.
// o índice da posição do caractere ou um indicador de ausência (-1).
char *find_newline_in_buffer(char *buffer, int fd)
{
	char *tmp;
//	ssize_t bytes_read;

//	bytes_read = 0;
	tmp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!tmp)
		return NULL;
	ft_strlcpy(tmp, buffer, BUFFER_SIZE + 1);
	while (ft_strchr(tmp, '\n') == 0)
	{
		tmp = malloc(sizeof(char) * BUFFER_SIZE + 1);
		bytes_read = read(fd, tmp + ft_strlen(tmp), (BUFFER_SIZE - ft_strlen(tmp)));
		if (!bytes_read)
			return NULL;
	}
	printf("%s", buffer);
	return NULL;
}

char *get_next_line(int fd)
{
	static char *buffer;
	buffer = NULL;

	if (!buffer)
	{
		buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buffer)
			return NULL;
		buffer = ft_memset(buffer, 0, BUFFER_SIZE);
		read(fd, buffer, BUFFER_SIZE);
	}
	find_newline_in_buffer(buffer);
	return (buffer);
}

int	main(void)
{
	int	fd;
	char *buffer;
	fd = open("arquivo.txt", O_RDONLY);

	// int i;
	// i = 0;
	buffer = get_next_line(fd);
	free(buffer);
	// while (buffer == (get_next_line(fd) != NULL))
	// {
	// 	printf("%s", buffer);
	// 	free(buffer);
	// }
	close(fd);
	return (0);
}

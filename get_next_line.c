/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gserafio <gserafio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:18:11 by gustavo-lin       #+#    #+#             */
/*   Updated: 2024/12/19 20:03:40 by gserafio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static char *extract_line(char **buffer)
{
	char	*new_line;
	char	*line;
	int		line_length;

	if (*buffer == NULL)
		return NULL;
	line_length = 0;
	new_line = ft_strchr(*buffer, '\n');
	if (new_line == NULL && *buffer != NULL)
	{
		line = malloc(sizeof(char) * (ft_strlen(*buffer) + 1));
		ft_strlcpy(line, *buffer, (ft_strlen(*buffer)+ 1));
		*buffer = NULL;
		return line;
	}
	line_length = new_line - *buffer;
	line = malloc(sizeof(char) * line_length + 2);
	if (!line)
		return NULL;
	ft_strlcpy(line, *buffer, line_length + 2);
	ft_strlcpy(*buffer, new_line + 1, ft_strlen(new_line));
	return line;
}

static char *find_newline_in_buffer(char **buffer, int fd)
{
	ssize_t bytes_read;
	char	*buffer_to_concat;
	char	*tmp;

	bytes_read = 0;
	buffer_to_concat = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer_to_concat)
		return NULL;
	buffer_to_concat[0] = '\0';
	while (ft_strchr(buffer_to_concat, '\n') == 0)
	{
		bytes_read = read(fd, buffer_to_concat, BUFFER_SIZE);
		if (bytes_read == 0)
			break;
		buffer_to_concat[bytes_read] = '\0';
		tmp = *buffer;
		*buffer = ft_strjoin(*buffer, buffer_to_concat);
		if (!*buffer)
			return NULL;
		free(tmp);
	}
	free(buffer_to_concat);
	return *buffer;
}

char *get_next_line(int fd)
{
	static char *buffer;
	int			*ptr_has_new_line;
	char		*buffer_to_return;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0))
		return NULL;
	if (!buffer)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return NULL;
	}
	buffer = find_newline_in_buffer(&buffer, fd);
	if (!buffer)
	{
		return NULL;
		free (buffer);	
	}
	buffer_to_return = extract_line(&buffer);
	if (!buffer_to_return)
		return NULL;
	return (buffer_to_return);
}

int	main(void)
{
	int	fd;
	char *buffer;
	fd = open("arquivo.txt", O_RDONLY);
	
	buffer = NULL;
	int i;
	i = 0;
	// buffer = get_next_line(fd);
	// printf("Buffer final %s", buffer);
	// free(buffer);
	while ((buffer = get_next_line(fd)) != NULL) {
		printf("%s", buffer);
		free(buffer); // Não esqueça de liberar a memória alocada para cada linha.
	}
	close(fd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gustavo-linux <gustavo-linux@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 00:18:08 by gustavo-lin       #+#    #+#             */
/*   Updated: 2024/12/13 02:13:44 by gustavo-lin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

t_list				*malloc_new_t_list(void);
int					find_new_line(t_list *new_node, int *no_new_line);
char				*get_next_line(int fd);
void				free_memory_assign_new_content(t_list **node_to_be_freed,
						t_list *tmp, int pos_n);
char				*ft_strdup(char *s);
size_t				ft_strlcat(char *dst, char *src, size_t size);

#endif
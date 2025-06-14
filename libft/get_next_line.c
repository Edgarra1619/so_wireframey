/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:01:13 by edgribei          #+#    #+#             */
/*   Updated: 2025/05/08 15:15:42 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd)
{
	static char	buffer[1024][BUFFER_SIZE + 1];
	char		*str;
	char		*end;
	ssize_t		bytes_read;

	if (fd < 0 || fd > 1024)
		return (NULL);
	str = NULL;
	bytes_read = BUFFER_SIZE;
	while (1)
	{
		if (!buffer[fd][0])
			bytes_read = read(fd, buffer[fd], BUFFER_SIZE);
		if (bytes_read == -1)
			return (clear_all(str, buffer[fd], BUFFER_SIZE));
		end = ft_findend(buffer[fd], '\n', BUFFER_SIZE);
		if (end - buffer[fd] == 0 && !*end)
			return (str);
		if (!ft_strappend(&str, buffer[fd], end - buffer[fd] + 1))
			return (NULL);
		ft_strlcpy_zero(buffer[fd], end + (*end == '\n'), BUFFER_SIZE);
		if (*ft_findend(str, '\n', (size_t) - 1) || bytes_read < BUFFER_SIZE)
			return (str);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:01:29 by edgribei          #+#    #+#             */
/*   Updated: 2025/05/08 13:52:48 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_findend(char *str, char term, size_t size)
{
	size_t	i;

	i = 0;
	while (str[i] && i < size && str[i] != term)
		i++;
	return (str + i);
}

size_t	ft_strlcpy_zero(char *dst, const char *src, size_t size)
{
	size_t	src_size;
	size_t	i;

	i = 0;
	src_size = 0;
	while (src[src_size])
		src_size++;
	while (i + 1 < size && i < src_size)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < size)
		dst[i++] = 0;
	return (src_size);
}

//appends to s1 on a new block of memory, freeing the old one and properly
//setting s1 = NULL
char	*ft_strappend(char **s1, const char *s2, size_t s2_size)
{
	size_t	i;
	char	*str;

	i = 0;
	while (*s1 && (*s1)[i])
		i++;
	str = malloc(sizeof(char) * (i + s2_size + 1));
	if (!str)
	{
		free(*s1);
		*s1 = NULL;
		return (NULL);
	}
	if (*s1)
		ft_strlcpy_zero(str, *s1, i + s2_size + 1);
	ft_strlcpy_zero(str + i, s2, s2_size + 1);
	free(*s1);
	*s1 = str;
	return (str);
}

void	*clear_all(char *str, char *buffer, size_t size)
{
	free(str);
	ft_strlcpy_zero(buffer, "", size);
	return (NULL);
}

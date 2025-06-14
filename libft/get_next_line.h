/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:00:49 by edgribei          #+#    #+#             */
/*   Updated: 2025/05/08 13:37:44 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stddef.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_findend(char *str, char term, size_t size);
char	*ft_strappend(char **s1, const char *s2, size_t s2_size);
size_t	ft_strlcpy_zero(char *dst, const char *src, size_t size);
void	*clear_all(char *str, char *buffer, size_t size);

#endif

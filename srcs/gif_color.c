/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gif_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:41:40 by edgribei          #+#    #+#             */
/*   Updated: 2025/07/10 17:41:42 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <color.h>

t_color	*parse_color_table(t_color *const table, const int size, const int fd)
{
	int	i;

	i = 0;
	while (i < size)
	{
		table[i].color = 0xFFFFFFFF;
		read(fd, &table[i].r, 1);
		read(fd, &table[i].g, 1);
		read(fd, &table[i].b, 1);
		i++;
	}
	return (table);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:58:18 by edgribei          #+#    #+#             */
/*   Updated: 2025/04/30 14:22:45 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

enum	e_std_colors
{
	RED = 0xFFFF0000,
	GREEN = 0xFF00FF00,
	BLUE = 0xFF0000FF,
	WHITE = 0xFFFFFFFF,
	BLACK = 0xFF000000,
};

typedef union u_color
{
	int	color;
	unsigned int ucolor;
	struct
	{
		unsigned char	a;
		unsigned char	r;
		unsigned char	g;
		unsigned char	b;
	}	s_rgba;
}	t_color;

t_color	color_lerp(t_color a, t_color b, float t);
#endif

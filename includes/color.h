/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:58:18 by edgribei          #+#    #+#             */
/*   Updated: 2025/05/27 13:56:23 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

enum	e_std_colors
{
	RED = 0xFFFF0000,
	GREEN = 0xFF00FF00,
	BLUE = 0xFF0000FF,
	YELLOW = 0xFFFFFF00,
	WHITE = 0xFFFFFFFF,
	BLACK = 0xFF000000,
};

//preferably, this would have some anonymous structs and unions so
//I could actually pad some
typedef union u_color
{
	int				color;
	unsigned int	ucolor;
	char			gif_color[4]; // use + 1 to avoid having to pad this one
	struct
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
	}	s_rgba;
}	t_color;

t_color	color_lerp(const t_color a, const t_color b, const float t);
t_color	get_height_color(const int z);
#endif

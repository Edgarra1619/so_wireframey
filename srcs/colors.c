/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:52:05 by edgribei          #+#    #+#             */
/*   Updated: 2025/05/14 19:06:46 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_math.h>
#include <color.h>

t_color	color_sum(const t_color a, const t_color b)
{
	t_color	c;

	c.s_rgba.a = clamp(a.s_rgba.a + b.s_rgba.a, 0, 255);
	c.s_rgba.r = clamp(a.s_rgba.r + b.s_rgba.r, 0, 255);
	c.s_rgba.g = clamp(a.s_rgba.g + b.s_rgba.g, 0, 255);
	c.s_rgba.b = clamp(a.s_rgba.b + b.s_rgba.b, 0, 255);
	return (c);
}

t_color	color_lerp(const t_color a, const t_color b, const float t)
{
	t_color	c;

	if (t <= 0)
		return (a);
	if (t >= 1)
		return (b);
	c.s_rgba.a = lerp(a.s_rgba.a, b.s_rgba.a, t);
	c.s_rgba.r = lerp(a.s_rgba.r, b.s_rgba.r, t);
	c.s_rgba.g = lerp(a.s_rgba.g, b.s_rgba.g, t);
	c.s_rgba.b = lerp(a.s_rgba.b, b.s_rgba.b, t);
	return (c);
}

//height below 0 is BLUE
//height 0 is YELLOW
//height 20 is GREEN
//height 40 and above is WHITE
//height above 40 is RED
t_color	get_height_color(const int z)
{
	if (z < -40)
		return (color_lerp((t_color) 0xFF1010FF, (t_color) BLUE, (float) ((-z) - 20) / 100));
	if (z < 60)
		return (color_lerp((t_color) 0XFF1111FF, (t_color) 0xFFA0A0FF,
				(float) z + 40 / (float) 200));
	if (z < 100)
		return (color_lerp((t_color) 0x00A0A0FF, (t_color) 0x00C0C0FF ,
				((float) z - 60) / (float) 100));
	return (color_lerp((t_color) RED, (t_color) RED ,
			((float) z - 80) / (float) 100));
}

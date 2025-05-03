/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:52:05 by edgribei          #+#    #+#             */
/*   Updated: 2025/05/02 18:31:48 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_math.h>
#include <color.h>

t_color	color_sum(t_color a, t_color b)
{
	t_color	c;

	c.s_rgba.a = clamp((int) a.s_rgba.a + (int) b.s_rgba.a, 0, 255);
	c.s_rgba.r = clamp((int) a.s_rgba.r + (int) b.s_rgba.r, 0, 255);
	c.s_rgba.g = clamp((int) a.s_rgba.g + (int) b.s_rgba.g, 0, 255);
	c.s_rgba.b = clamp((int) a.s_rgba.b + (int) b.s_rgba.b, 0, 255);
	return (c);
}

t_color	color_lerp(t_color a, t_color b, float t)
{
	t_color	c;

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
t_color	get_height_color(int z)
{

	if (z < -10)
		return (color_lerp((t_color) 0xFF1010FF, (t_color) BLUE, (float) (-z) - 10 / 10));
	if (z < 30)
		return (color_lerp((t_color) 0XFF1010FF, (t_color) 0xFFF0F0FF,
				(float) z / (float) 30));
	if (z < 50)
		return (color_lerp((t_color) 0xFFA0A0FF, (t_color) WHITE ,
				((float) z - 30) / (float) 20));
	return (color_lerp((t_color) WHITE, (t_color) RED ,
			((float) z - 50) / (float) 100));

}

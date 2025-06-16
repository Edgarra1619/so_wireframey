/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:52:05 by edgribei          #+#    #+#             */
/*   Updated: 2025/06/16 18:40:56 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <my_math.h>
#include <color.h>

t_color	color_sum(const t_color a, const t_color b)
{
	t_color	c;

	c.r = clamp(a.r + b.r, 0, 255);
	c.g = clamp(a.g + b.g, 0, 255);
	c.b = clamp(a.b + b.b, 0, 255);
	return (c);
}

t_color	color_lerp(const t_color a, const t_color b, const float t)
{
	static const float	lower_bound = (float) 1 / 255;
	static const float	upper_bound = (float) 254 / 255;

	if (t <= lower_bound)
		return (a);
	if (t >= upper_bound)
		return (b);
	return ((t_color){
		{
			a.b + (b.b - a.b) * t,
			a.g + (b.g - a.g) * t,
			a.r + (b.r - a.r) * t,
			a.a + (b.a - a.a) * t
		}
	});
}

t_color	color_flerp(const t_color a, const t_color b, const float t)
{
	return ((t_color){
		{
			a.b + (b.b - a.b) * t,
			a.g + (b.g - a.g) * t,
			a.r + (b.r - a.r) * t,
			a.a + (b.a - a.a) * t
		}
	});
}

//height below 0 is BLUE
//height 0 is YELLOW
//height 20 is GREEN
//height 40 and above is WHITE
//height above 40 is RED
t_color	get_height_color(const int z)
{
	if (z < -40)
		return (color_lerp((t_color) 0xFF1010FF,
				(t_color) BLUE, (float)((-z) - 20) / 100));
	if (z < 60)
		return (color_lerp((t_color) 0XFF1111FF, (t_color) 0xFFA0A0FF,
				(float) z + 40 / (float) 200));
	if (z < 100)
		return (color_lerp((t_color) 0x00A0A0FF, (t_color) 0x00C0C0FF,
				((float) z - 60) / (float) 100));
	return (color_lerp((t_color) RED, (t_color) RED,
			((float) z - 80) / (float) 100));
}

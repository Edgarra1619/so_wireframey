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

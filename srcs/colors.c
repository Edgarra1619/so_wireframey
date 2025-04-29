#include <my_math.h>
#include <color.h>

t_color	color_sum(t_color a, t_color b)
{
	t_color	c;

	c.rgba.a = clamp((int) a.rgba.a + (int) b.rgba.a, 0, 255);
	c.rgba.r = clamp((int) a.rgba.r + (int) b.rgba.r, 0, 255);
	c.rgba.g = clamp((int) a.rgba.g + (int) b.rgba.g, 0, 255);
	c.rgba.b = clamp((int) a.rgba.b + (int) b.rgba.b, 0, 255);
	return (c);
}

t_color	color_lerp(t_color a, t_color b, float t)
{
	t_color	c;

	c.rgba.a = lerp(a.rgba.a, b.rgba.a, t);
	c.rgba.r = lerp(a.rgba.r, b.rgba.r, t);
	c.rgba.g = lerp(a.rgba.g, b.rgba.g, t);
	c.rgba.b = lerp(a.rgba.b, b.rgba.b, t);
	return (c);
}

#include <vector.h>
#include <mlx.h>
#include <render.h>
#include <color.h>

inline void	put_pixel_image(char *image, int sline, t_vec2 position, t_color color)
{
	((int*) (image + position.y * sline))[position.x] = color.color;
}
static void	put_pixel_image(char *image, int sline, t_vec2 position, t_color color)
{

	((int*) (image + position.y * sline))[position.x] = color.color;
}

void	put_square(void *image, t_vec2 UL, t_vec2 DR, t_color color)
{
	int	x;
	int	sline;
	char	*bits;

	bits = mlx_get_data_addr(image, &x, &sline, &x);
	while (UL.y <= DR.y)
	{
		x = UL.x;
		while (x <= DR.x)
		{
			put_pixel_image(bits, sline, (t_vec2) {x, UL.y}, color);
			x++;
		}
		UL.y++;
	}
}

// y = mx + b
void	put_line(void *image, t_vec2 a, t_vec2 b, t_color color)
{
	float		m;
	int			k;
	int			i[2];
	int			sline;
	const char	*bits = mlx_get_data_addr(image, &k, &sline, &k);

	if (a.x != b.x)
	{
		m = (float) (b.y - a.y) / (b.x - a.x);
		k = a.y - m * a.x;
		i[0] = (a.x * (a.x < b.x)) + (b.x * (b.x < a.x));
		i[1] = (a.x * (a.x > b.x)) + (b.x * (b.x > a.x));
		while (i[0]++ < i[1])
			put_pixel_image((char *) bits, sline, (t_vec2) {i[0], i[0] * m + k}, color);
	}
	else if (a.y != b.y)
	{
		m = (float) (b.x - a.x) / (b.y - a.y);
		k = a.x - m * a.y;
		i[0] = (a.y * (a.y < b.y)) + (b.y * (b.y < a.y));
		i[1] = (a.y * (a.y > b.y)) + (b.y * (b.y > a.y));
		while (i[0]++ < i[1])
			put_pixel_image((char *) bits, sline, (t_vec2) {i[0] * m + k, i[0]}, color);
	}
	put_pixel_image((char *) bits, sline, (t_vec2) {a.x, a.y}, color);
}

void	put_grad_line(void *image, t_vec2 a, t_vec2 b, t_color colora, t_color colorb)
{
	float		m;
	int			k;
	int			i[2];
	int			sline;
	const char	*bits = mlx_get_data_addr(image, &k, &sline, &k);

	if (a.x != b.x)
	{
		m = (float) (b.y - a.y) / (b.x - a.x);
		k = a.y - m * a.x;
		i[0] = (a.x * (a.x < b.x)) + (b.x * (b.x < a.x));
		i[1] = (a.x * (a.x > b.x)) + (b.x * (b.x > a.x));
		while (i[0]++ < i[1])
			put_pixel_image((char *) bits, sline, (t_vec2) {i[0], i[0] * m + k}, color_lerp(colora, colorb, 0.5));
	}
	else if (a.y != b.y)
	{
		m = (float) (b.x - a.x) / (b.y - a.y);
		k = a.x - m * a.y;
		i[0] = (a.y * (a.y < b.y)) + (b.y * (b.y < a.y));
		i[1] = (a.y * (a.y > b.y)) + (b.y * (b.y > a.y));
		while (i[0]++ < i[1])
			put_pixel_image((char *) bits, sline, (t_vec2) {i[0] * m + k, i[0]}, color_lerp(colora, colorb, 0.5));
	}
	put_pixel_image((char *) bits, sline, (t_vec2) {a.x, a.y}, color_lerp(colora, colorb, 0.5));
}

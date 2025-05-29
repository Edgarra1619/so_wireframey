#include <color.h>
#include <state.h>
#include <libft.h>

static inline void	put_pixel_image(t_image *const image, const t_vec2 position, const t_color color)
{
	if (position.x < 0 || position.y < 0 ||
			position.x >= WINDOW_WIDTH || position.y >= WINDOW_HEIGHT)
		return ;
	((int*) (image->data + position.y * image->sline))[position.x] = color.color;
}

/*
void	fput_pixel_image(char *image, int sline, t_vec2 position, t_color color)
{
	((int*) (image + position.y * sline))[position.x] = color.color;
}
*/

void	clear_image(t_image *const image)
{
	ft_bzero(image->data, image->size.y * image->sline);
}

void	put_square(t_image *const image, const t_vec2 UL, const t_vec2 DR, const t_color color)
{
	int	x;
	int	y;

	y = UL.y - 1;
	while (++y <= DR.y)
	{
		x = UL.x - 1;
		while (++x <= DR.x)
			put_pixel_image(image, (t_vec2) {x, y}, color);
	}
}

void	put_line(t_image *image, t_vec2 a, t_vec2 b, t_color color)
{
	float		m;
	int			k;
	int			i[2];

	if (!in_bounds(image, a) && !in_bounds(image, b))
		return ;
	if (a.x != b.x)
	{
		m = (float) (b.y - a.y) / (b.x - a.x);
		k = a.y - m * a.x;
		i[0] = (a.x * (a.x < b.x)) + (b.x * (b.x < a.x));
		i[1] = (a.x * (a.x > b.x)) + (b.x * (b.x > a.x));
		while (i[0]++ < i[1])
			put_pixel_image(image, (t_vec2) {i[0], i[0] * m + k}, color);
	}
	if (a.y != b.y)
	{
		m = (float) (b.x - a.x) / (b.y - a.y);
		k = a.x - m * a.y;
		i[0] = (a.y * (a.y < b.y)) + (b.y * (b.y < a.y));
		i[1] = (a.y * (a.y > b.y)) + (b.y * (b.y > a.y));
		while (i[0]++ < i[1])
			put_pixel_image(image, (t_vec2) {i[0] * m + k, i[0]}, color);
	}
	put_pixel_image(image, (t_vec2) {a.x, a.y}, color);
}

void	put_grad_line(void *image, const t_vec2 a, const t_vec2 b,
				   const t_color colora, const t_color colorb)
{
	float		m;
	int			k;
	int			i[3];

	if (!in_bounds(image, a) && !in_bounds(image, b))
		return ;
	if (a.x != b.x)
	{
		m = (float) (b.y - a.y) / (b.x - a.x);
		k = a.y - m * a.x;
		i[0] = (a.x * (a.x < b.x)) + (b.x * (b.x < a.x));
		i[2] = i[0];
		i[1] = (a.x * (a.x > b.x)) + (b.x * (b.x > a.x));
		while (i[0]++ < i[1])
			put_pixel_image(image, (t_vec2) {i[0], i[0] * m + k},
					color_lerp(colora, colorb,
						(float) (i[0] - i[2]) / (float) (i[1] - i[2])));
	}
	if (a.y != b.y)
	{
		m = (float) (b.x - a.x) / (b.y - a.y);
		k = a.x - m * a.y;
		i[0] = (a.y * (a.y < b.y)) + (b.y * (b.y < a.y));
		i[2] = i[0];
		i[1] = (a.y * (a.y > b.y)) + (b.y * (b.y > a.y));
		while (i[0]++ < i[1])
			put_pixel_image(image, (t_vec2) {i[0] * m + k, i[0]},
					color_lerp(colora, colorb,
						 (float) (i[0] - i[2]) / (float) (i[1] - i[2])));
	}
	put_pixel_image(image, (t_vec2) {a.x, a.y}, colora);
}

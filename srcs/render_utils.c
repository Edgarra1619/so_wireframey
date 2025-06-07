#include <vector.h>
#include <my_math.h>
#include <color.h>
#include <state.h>
#include <libft.h>

static int	in_bounds(const t_image *const image, const t_vec2 position)
{
	if (position.x >= image->size.x || position.x < 0 ||
		position.y >= image->size.y || position.y < 0)
		return (0);
	return (1);
}

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
	const int		steps = max(abs(a.x - b.x), abs(a.y - b.y));
	const t_vecf2	step_size = (t_vecf2) {((float) b.x - a.x) / 16, ((float) b.y - a.y) / 16};
	int				count;
	t_vecf2			i;

	if (!in_bounds(image, a) && !in_bounds(image, b))
		return ;
	count = 0;
	i = (t_vecf2){a.x, a.y};
	while (count < steps)
	{
		put_pixel_image(image, (t_vec2) {(int) i.x, (int) i.y},  color);
		i = sum_vecf2(i, step_size);
		count++;
	}
	put_pixel_image(image, b, color);
}

void	put_grad_line(t_image *image, t_vec2 a, t_vec2 b, t_color colora, t_color colorb)
{
	const int		steps = max(abs(a.x - b.x), abs(a.y - b.y));
	const t_vecf2	step_size = (t_vecf2) {((float) b.x - a.x) / steps, ((float) b.y - a.y) / steps};
	int				count;
	t_vecf2			i;

	if (!in_bounds(image, a) && !in_bounds(image, b))
		return ;
	count = 0;
	i = (t_vecf2){a.x, a.y};
	while (count < steps)
	{
		put_pixel_image(image, (t_vec2) {(int) i.x, (int) i.y},  color_lerp(colorb, colora, (float) count / steps));
		i = sum_vecf2(i, step_size);
		count++;
	}
	put_pixel_image(image, b, colorb);
}

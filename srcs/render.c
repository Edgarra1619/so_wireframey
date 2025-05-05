#include <state.h>
#include <math.h>
#include <vector.h>
#include <mlx.h>
#include <render.h>
#include <color.h>

inline int	in_bounds(t_image *image, t_vec2 position)
{
	if (position.x >= image->size.x || position.x < 0 ||
		position.y >= image->size.y || position.y < 0)
		return (0);
	return (1);
}

inline void	put_pixel_image(t_image *image, t_vec2 position, t_color color)
{
	if (position.x < 0 || position.y < 0 ||
			position.x >= WINDOW_WIDTH || position.y >= WINDOW_HEIGHT)
		return ;
	((int*) (image->data + position.y * image->sline))[position.x] = color.color;
}
/*
static void	put_pixel_image(char *image, int sline, t_vec2 position, t_color color)
{
	((int*) (image + position.y * sline))[position.x] = color.color;
}
*/

void	put_square(t_image *image, t_vec2 UL, t_vec2 DR, t_color color)
{
	int	x;

	while (UL.y <= DR.y)
	{
		x = UL.x;
		while (x <= DR.x)
		{
			put_pixel_image(image, (t_vec2) {x, UL.y}, color);
			x++;
		}
		UL.y++;
	}
}

// y = mx + b
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

void	put_grad_line(void *image, t_vec2 a, t_vec2 b, t_color colora, t_color colorb)
{
	float		m;
	int			k;
	int			i[3];

	if (a.x != b.x)
	{
		m = (float) (b.y - a.y) / (b.x - a.x);
		k = a.y - m * a.x;
		i[0] = (a.x * (a.x < b.x)) + (b.x * (b.x < a.x));
		i[2] = i[0];
		i[1] = (a.x * (a.x > b.x)) + (b.x * (b.x > a.x));
		while (i[0]++ < i[1])
			put_pixel_image(image, (t_vec2) {i[0], i[0] * m + k},
					color_lerp(colorb, colora,
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
					color_lerp(colorb, colora,
						 (float) (i[0] - i[2]) / (float) (i[1] - i[2])));
	}
	put_pixel_image(image, (t_vec2) {a.x, a.y}, color_lerp(colora, colorb, 0.5));
}

t_vec2	world_to_camera(const t_state *state, t_vec3 position)
{
	t_vec2	result;	
	const float	sin_rotx = sin((float) state->camera.rot.x / 180 * M_PI);
	const float	cos_rotx = cos((float) state->camera.rot.x / 180 * M_PI);
	const float	sin_roty = sin((float) state->camera.rot.y / 180 * M_PI);
	const float	cos_roty = cos((float) state->camera.rot.y / 180 * M_PI);

	position = sum_vec3(position, (t_vec3){-state->mapw/2, -state->maph/2, 0});
	position = sum_vec3(position, state->camera.pos);
	result.x = WINDOW_WIDTH / 2 + 16 * ((float) position.x * cos_rotx -
			(float) position.y * sin_rotx);
	result.y = WINDOW_HEIGHT / 2 - ((float) position.z * cos_roty) / 5 +
			16 * sin_roty *
			((float) position.x * sin_rotx +
			(float) position.y * cos_rotx);
//	result = sum_vec2(result, (t_vec2) {-state->camera.position.y, -state->camera.position.x});
//	(position.z - camera->position.z) / 5;
	return (result);
}

void	render_map(t_image *img, t_state *state)
{
	int	x;
	int	y;

	y = 0;
	while (y < state->maph)
	{
		x = 0;
		while (x < state->mapw)
		{
			if (y != state->maph - 1)
				put_grad_line(img, world_to_camera(state, (t_vec3) {x, y, state->map[x][y]}),
					world_to_camera(state, (t_vec3) {x, y + 1, state->map[x][y + 1]}),
					get_height_color(state->map[x][y]), get_height_color(state->map[x][y + 1]));
			if (x != state->mapw - 1)
				put_grad_line(img, world_to_camera(state,(t_vec3) {x, y, state->map[x][y]}),
					world_to_camera(state, (t_vec3) {x + 1, y, state->map[x + 1][y]}),
					get_height_color(state->map[x + 1][y]), get_height_color(state->map[x][y]));
			x++;
		}
		y++;
	}
}

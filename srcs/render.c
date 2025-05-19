#include <state.h>
#include <math.h>
#include <strings.h>
#include <vector.h>
#include <mlx.h>
#include <render.h>
#include <color.h>

int	in_bounds(const t_image *const image, const t_vec2 position)
{
	if (position.x >= image->size.x || position.x < 0 ||
		position.y >= image->size.y || position.y < 0)
		return (0);
	return (1);
}

inline void	put_pixel_image(t_image *const image, const t_vec2 position, const t_color color)
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

t_vec2	world_to_camera(const t_state *state, t_vec3 position, const float sin_rotx, const float cos_rotx, const float sin_roty, const float cos_roty)
{
	t_vec2	result;

	position.x += state->camera.pos.x - state->mapw/2;
	position.y += state->camera.pos.y - state->maph/2;
	position.z += state->camera.pos.z;
//	position = sum_vec3(position, (t_vec3){-state->mapw/2, -state->maph/2, 0});
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

void	pre_calculate_map(t_state *state)
{
	const float	sin_rotx = sin((float) state->camera.rot.x / 180 * M_PI);
	const float	cos_rotx = cos((float) state->camera.rot.x / 180 * M_PI);
	const float	sin_roty = sin((float) state->camera.rot.y / 180 * M_PI);
	const float	cos_roty = cos((float) state->camera.rot.y / 180 * M_PI);
	int		x;
	int		y;
	const	int maph = state->maph;
	const	int mapw = state->mapw;
	const int	**const map = (const int **)state->map;

	y = -1;
	while (++y < maph)
	{
		x = -1;
		while (++x < mapw)
		{
			state->pre_map[x][y] = world_to_camera(state, (t_vec3) {x, y, map[x][y]}, sin_rotx, cos_rotx, sin_roty, cos_roty);
			state->color_map[x][y] = get_height_color(map[x][y]);
		}
	}
}

void	render_map(t_image *img, t_state *state)
{
	int		x;
	int		y;
	const int	maph = state->maph;
	const int	mapw = state->mapw;

	pre_calculate_map(state);
	y = -1;
	while (++y < maph)
	{
		x = -1;
		while (++x < mapw)
		{
			if (y != maph - 1)
				put_grad_line(img, state->pre_map[x][y],
					state->pre_map[x][y + 1],
					state->color_map[x][y], state->color_map[x][y + 1]);
			if (x != mapw - 1)
				put_grad_line(img, state->pre_map[x][y],
					state->pre_map[x + 1][y],
					state->color_map[x][y], state->color_map[x + 1][y]);
		}
	}
}

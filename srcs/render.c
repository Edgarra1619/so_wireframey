#include <color.h>
#include <libft.h>
#include <map.h>
#include <math.h>
#include <mlx.h>
#include <render.h>
#include <state.h>
#include <vector.h>

int	in_bounds(const t_image *const image, const t_vec2 position)
{
	if (position.x >= image->size.x || position.x < 0 ||
		position.y >= image->size.y || position.y < 0)
		return (0);
	return (1);
}

t_vec2	world_to_camera(const t_camera *camera, t_vec3 position)
{
	t_vec2	result;

	position.x += camera->pos.x;
	position.y += camera->pos.y;
	position.z += camera->pos.z;
	result.x = WINDOW_WIDTH / 2.0 + camera->zoom * ((float) position.x * camera->cos_rotx -
			(float) position.y * camera->sin_rotx);
	result.y = WINDOW_HEIGHT / 2.0 + camera->zoom *
		( - ((float) position.z * camera->cos_roty) / camera->vertical_scale +
		camera->sin_roty * ((float) position.x * camera->sin_rotx +
		(float) position.y * camera->cos_rotx));
//	result = sum_vec2(result, (t_vec2) {-state->camera.position.y, -state->camera.position.x});
//	(position.z - camera->position.z) / 5;
	return (result);
}

void	pre_calculate_map(const t_camera *const camera, const t_map *const map, t_vec2 **const pre_map)
{
	int		x;
	int		y;
	const	int maph = map->size.y;
	const	int mapw = map->size.x;

	y = -1;
	while (++y < maph)
	{
		x = -1;
		while (++x < mapw)
			pre_map[x][y] = world_to_camera(camera,
					(t_vec3) {x, y, map->height_map[x][y]});
	}
}

//TODO make the render opt between front and back rendering according
//to the angle of the camera;
void	render_map(t_image *const img, const t_map *const map,
			const t_camera *const camera, t_vec2 **pre_map)
{
	int		x;
	int		y;
	const int	maph = map->size.y;
	const int	mapw = map->size.x;

	pre_calculate_map(camera, map, pre_map);
	y = -1;
	while (++y < maph)
	{
		x = -1;
		while (++x < mapw)
		{
			if (y != maph - 1)
				put_grad_line(img, pre_map[x][y],
					pre_map[x][y + 1],
					map->color_map[x][y], map->color_map[x][y + 1]);
			if (x != mapw - 1)
				put_grad_line(img, pre_map[x][y],
					pre_map[x + 1][y],
					map->color_map[x][y], map->color_map[x + 1][y]);
		}
	}
}

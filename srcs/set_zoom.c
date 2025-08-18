#include <limits.h>
#include <state.h>
#include <my_math.h>
#include <render.h>

t_vec2	world_to_camera(const t_camera *camera, t_vec3 pos);


void	set_camera(t_camera *camera, t_map *map)
{
	int		maxp;
	int		minp;
	t_vec3	i;
	t_vec2	tmp;

	camera->zoom = 1;
	camera->vertical_scale = 1;
	maxp = INT_MIN;
	minp = INT_MAX;
	i.x = 0;
	while (i.x < map->size.x)
	{
		i.y = 0;
		while (i.y < map->size.y)
		{
			i.z = map->height_map[i.x][i.y];
			tmp = world_to_camera(camera,
						(t_vec3) {map->size.y - i.y, i.x, i.z});
			minp = min(tmp.y, minp);
			maxp = max(tmp.y, maxp);
			i.y++;
		}
		i.x++;
	}
	camera->zoom = min((float)(WINDOW_WIDTH * 4) /
			(5 * max(map->size.x, map->size.y)),
			(WINDOW_HEIGHT * 4) / (5 * (maxp - minp)));
	camera->pos.y = camera->zoom * ((WINDOW_HEIGHT * 9) / 10 - minp);

/*
screenpos.y = campos + window - camzoom * point
oldscreenpos.y = window - point
campos = screenpos.y - window + camzoom * point
campos = screenpos.y - window + camzoom * (window - minp)
*/
}

/*
float	set_zoom(t_camera *camera, t_map *map)
{
	static const float	height = (float) WINDOW_HEIGHT * 8 / 10;
	float				zoom;
	t_vec3				i;

	camera->zoom = 1;
	camera->vertical_scale = 1;
	zoom = (float)(WINDOW_WIDTH * 4) / (5 * max(map->size.x, map->size.y));
	i.x = 0;
	while (i.x < map->size.x)
	{
		i.y = 0;
		while (i.y < map->size.y)
		{
			i.z = map->height_map[i.x][i.y];
			zoom = minf(zoom, height
					/ ((float) 9 * WINDOW_HEIGHT / 10
						- world_to_camera(camera, (t_vec3)
						{map->size.y - i.y, i.x, i.z}).y));
			i.y++;
		}
		i.x++;
	}
	return (zoom);
}
*/

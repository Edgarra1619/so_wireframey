/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:49:03 by edgribei          #+#    #+#             */
/*   Updated: 2025/06/16 19:19:46 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <color.h>
#include <libft.h>
#include <map.h>
#include <mlx.h>
#include <my_math.h>
#include <render.h>
#include <state.h>
#include <vector.h>

int	in_bounds(const t_image *const image, const t_vec2 position)
{
	if (position.x >= image->size.x || position.x < 0
		|| position.y >= image->size.y || position.y < 0)
		return (0);
	return (1);
}

t_vec2	world_to_camera(const t_camera *camera, t_vec3 pos)
{
	(void) camera;
	return ((t_vec2)
		{
			(float) WINDOW_WIDTH / 2 - camera->zoom * ((pos.x - pos.y) + camera->pos.x ),
			(float) 9 * WINDOW_HEIGHT / 10
			- camera->zoom * ((float)(pos.x + pos.y) / 2 - camera->pos.y + pos.z)
	});
}

void	pre_calculate_map(const t_camera *const camera,
					const t_map *const map, t_vec2 **const pre_map)
{
	const int	maph = map->size.y;
	const int	mapw = map->size.x;
	int			x;
	int			y;

	y = -1;
	while (++y < maph)
	{
		x = -1;
		while (++x < mapw)
			pre_map[x][y] = world_to_camera(
					camera, (t_vec3){maph - y, x,
					map->height_map[x][y]});
	}
}

void	render_map(t_image *const img, const t_map *const map,
			const t_camera *const camera, t_vec2 **pre_map)
{
	const t_vec2	iter = (t_vec2){
		1 * (camera->sin_rotx > 0) - 1 * (camera->sin_rotx <= 0),
		1 * (camera->cos_rotx > 0) - 1 * (camera->cos_rotx <= 0)};
	const t_vec2	mapsize = map->size;
	t_vec2			i;

	pre_calculate_map(camera, map, pre_map);
	i.y = (iter.y == -1) * (mapsize.y - 1);
	while (i.y < mapsize.y && i.y >= 0)
	{
		i.x = (iter.x == -1) * (mapsize.x - 1);
		while (i.x < mapsize.x && i.x >= 0)
		{
			if (i.y != mapsize.y - 1)
				put_grad_line(img,
					(t_vec2[2]){pre_map[i.x][i.y], pre_map[i.x][i.y + 1]},
					map->color_map[i.x][i.y], map->color_map[i.x][i.y + 1]);
			if (i.x != mapsize.x - 1)
				put_grad_line(img,
					(t_vec2[2]){pre_map[i.x][i.y], pre_map[i.x + 1][i.y]},
					map->color_map[i.x][i.y], map->color_map[i.x + 1][i.y]);
			i.x += iter.x;
		}
		i.y += iter.y;
	}
}

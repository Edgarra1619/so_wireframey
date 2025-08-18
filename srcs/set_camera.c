/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 17:07:39 by edgribei          #+#    #+#             */
/*   Updated: 2025/08/18 17:39:41 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <state.h>
#include <my_math.h>
#include <render.h>

t_vec2	world_to_camera(const t_camera *camera, t_vec3 pos);

void	set_camera(t_camera *camera, t_map *map)
{
	t_vec3	minmaxp;
	t_vec3	i;
	t_vec2	tmp;

	camera->zoom = 1;
	camera->vertical_scale = 1;
	minmaxp = (t_vec3){INT_MAX, INT_MIN, INT_MAX};
	i.x = -1;
	while (++i.x < map->size.x)
	{
		i.y = -1;
		while (++i.y < map->size.y)
		{
			i.z = map->height_map[i.x][i.y];
			tmp = world_to_camera(camera,
					(t_vec3){map->size.y - i.y, i.x, i.z});
			minmaxp = (t_vec3){min(tmp.y, minmaxp.x),
				max(tmp.y, minmaxp.y), min(i.z, minmaxp.z)};
		}
	}
	camera->zoom = min((float)(WINDOW_WIDTH * 4)
			/ (5 * max(map->size.x, map->size.y)),
			(float)(WINDOW_HEIGHT * 8) / (10 * (minmaxp.y - minmaxp.x)));
	camera->pos.y = minmaxp.z;
}

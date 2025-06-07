/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:58:36 by edgribei          #+#    #+#             */
/*   Updated: 2025/05/21 18:58:44 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <color.h>
#include <state.h>
#include <map.h>
#include <stdlib.h>
#include <math.h>
#include <vector.h>

int	new_map(t_map *map)
{
	const size_t	w = map->size.x;
	const size_t	h = map->size.y;
	size_t			i;

	map->height_map = ft_calloc(w, sizeof(int*));
	map->color_map = ft_calloc(w, sizeof(t_color*));
	if(!map->height_map || !map->color_map)
	{
		free(map->height_map);
		free(map->color_map);
		return (-1);
	}
	map->height_map[0] = ft_calloc(w * h, sizeof(int));
	map->color_map[0] = ft_calloc(w * h, sizeof(t_color));
	if(!map->height_map || !map->color_map)
	{
		free(map->height_map[0]);
		free(map->color_map[0]);
		free(map->height_map);
		free(map->color_map);
		return (-1);
	}
	i = 1;
	while (i < w)
	{
		map->height_map[i] = map->height_map[0] + i * h;
		map->color_map[i] = map->color_map[0] + i * h;
		i++;
	}
	return (0);
}

t_map	*copy_map(t_map *dest, t_list *list_src)
{
	const t_vec2	orig_size = dest->size;
	t_map			*src;

	if (!list_src)
	{
		new_map(dest);
		return (dest);
	}
	src = list_src->content;
	dest->size = src->size;
	if (new_map(dest) == -1)
		return (NULL);
	ft_memcpy(*(dest->color_map), *(src->color_map),
		sizeof(t_color) * src->size.x * src->size.y);
	ft_memcpy(*(dest->height_map), *(src->height_map),
		sizeof(int) * src->size.x * src->size.y);
	dest->size = orig_size;
	return (dest);
}

void	pre_map_alloc(void *stat)
{
	t_vec2	max_size;
	int		i;
	t_state	*const state = (t_state*) stat;

	max_size = (t_vec2){0, 0};
	i = 0;
	while (i < state->mapcount)
	{
		if (state->maps[i].size.x > max_size.x)
			max_size.x = state->maps[i].size.x;
		if (state->maps[i].size.y > max_size.y)
			max_size.y = state->maps[i].size.y;
		i++;
	}
	state->pre_map = ft_calloc(max_size.x, sizeof(t_vec2*));
	state->pre_map[0] = ft_calloc(max_size.x * max_size.y, sizeof(t_vec2));
	//TODO GUARD THIS
	i = 0;
	while (++i < max_size.x)
		state->pre_map[i] = state->pre_map[0] + i * max_size.y;
		//and guard this
}

/*
int	**test_map(int w, int h, t_state *state)
{
	int	**map;
	int	i;

	//TODO put ft_calloc here and guard it
	map = calloc(w, sizeof(int *));
	state->pre_map = calloc(w, sizeof(t_vec2*));
	state->color_map = calloc(w, sizeof(t_color*));
	i = 0;
	while (i < w)
	{
		map[i] = calloc(h, sizeof(int));
		state->pre_map[i] = calloc(h, sizeof(t_vec2));
		state->color_map[i] = calloc(h, sizeof(t_color));
		i++;
	}
	ocean_map (map, w, h);
	return (map);
}


void	ocean_map(int **map, int w, int h)
{
	static int	count;
	int			i;
	int			j;

	i = 0;
	while (i < w)
	{
		j = 0;
		while(j < h)
		{
			map[i][j] = sin((float) ((float)(i * 3 + count) / 5) / 2) * 15 +
				sin((float) ((float)(i * 1 + count) / 6) / 4) * 20 +
				cos((float) ((float)(i * 2 + count) / 2) * 2) * 3 +
				sin((float) ((float)(j * -1 + count) / 5) / 3) * 10 +
				cos((float) ((float)(j * 2 + count) / 2) / 2) * 15 +
				sin((float) ((float)(j + count) / 40) / 1) * 20 +
				cos((float) ((float)(j * - 3 + count) / 2) * 2) * 3;
			j++;
		}
		i++;
	}
	count++;
}
*/

void	free_map(void **map)
{
	free(map[0]);
	free(map);
}

void	free_maps(t_map *map, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free_map((void**) map[i].height_map);
		free_map((void**) map[i].color_map);
		i++;
	}
	free(map);
}

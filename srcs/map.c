/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:58:36 by edgribei          #+#    #+#             */
/*   Updated: 2025/05/05 14:15:55 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>
#include <stdlib.h>
#include <math.h>

int	**test_map(int w, int h)
{
	int	**map;
	int	i;

	//TODO put ft_calloc here
	map = calloc(w, sizeof(int *));
	i = 0;
	while (i < w)
	{
		map[i] = calloc(h, sizeof(int));
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
			map[i][j] = sin((float) (i + 3 + (float) count / 20) / 2) * 15 +
				sin((float) (i + 1 + (float) count / 12) / 4) * 20 +
				cos((float) (i + 2 + (float) count / 8) * 2) * 3 +
				sin((float) (j - 1 + (float) count / 20) / 3) * 10 +
				cos((float) (j + 2 + (float) count / 8) / 2) * 15 +
				sin((float) (j + (float) count / 40) / 4) * 20 +
				cos((float) (j - 3 + (float) count / 8) * 2) * 3;
			j++;
		}
		i++;
	}
	count++;
}

void	free_map(int **map, int w)
{
	int	i;

	i = 0;
	while (i < w)
		free(map[i++]);
	free(map);
}

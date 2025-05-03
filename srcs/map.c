/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:58:36 by edgribei          #+#    #+#             */
/*   Updated: 2025/05/02 18:07:39 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>
#include <stdlib.h>

int	**test_map(int *w, int *h)
{
	int	**map;
	int	i;
	int	j;

	*w = 10;
	*h = 10;
	//TODO put ft_calloc here
	map = calloc(*w, sizeof(int *));
	i = 0;
	while (i < *w)
	{
		j = 0;
		map[i] = calloc(*h, sizeof(int));
		while(j < *h)
		{
			map[i][j] = (rand() % 150) - 50;
			j++;
		}
		i++;
	}
	return (map);
}

void	free_map(int **map, int w)
{
	int	i;

	i = 0;
	while (i < w)
		free(map[i++]);
	free(map);
}

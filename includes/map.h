/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:08:02 by edgribei          #+#    #+#             */
/*   Updated: 2025/05/03 17:54:48 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include <vector.h>
# include <state.h>

int		**test_map(int w, int h, t_state *state);
//int		**parse_map(int fd, int *w, int *h);
void	free_map(int **map, int w);
void	ocean_map(int **map, int w, int h);



#endif

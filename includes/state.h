/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:00:14 by edgribei          #+#    #+#             */
/*   Updated: 2025/05/03 18:27:43 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H
# include <vector.h>

typedef struct s_camera
{
	t_vec3	pos;
	t_vec2	rot;
}	t_camera;

typedef struct s_state
{
	t_camera	camera;
	int			**map;
	int			mapw;
	int			maph;
	void	*mlx;
	void	*window;
	void	*buffer;
}	t_state;

#endif

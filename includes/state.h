/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:00:14 by edgribei          #+#    #+#             */
/*   Updated: 2025/05/02 13:50:34 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H
# include <vector.h>

typedef struct s_camera
{
	t_vec2	position;
	t_vec2	rotation;
}	t_camera;

typedef struct s_state
{
	t_camera	camera;
	int			**map;
	int			mapw;
	int			maph;

}	t_state;

#endif

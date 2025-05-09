/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:00:14 by edgribei          #+#    #+#             */
/*   Updated: 2025/05/05 14:27:14 by edgribei         ###   ########.fr       */
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

enum	e_input
{
	KEYCODEW = 1 << 0,
	KEYCODES = 1 << 1,
	KEYCODEA = 1 << 2,
	KEYCODED = 1 << 3,
	KEYCODEQ = 1 << 4,
	KEYCODEE = 1 << 5,
	BUTTONL = 1 << 6,
	BUTTONR = 1 << 7,
};

typedef struct	s_image
{
	void	*ptr;
	char	*data;
	int		sline;
	int		bpp;
	int		endian;
	t_vec2	size;
}	t_image;

//input will be handled as a flag
//0-5 will be wsadqe and 6-7 will be mouse buttons
typedef struct	s_state
{
	t_camera	camera;
	int			**map;
	t_vec2		**pre_map;
	int			mapw;
	int			maph;
	void		*mlx;
	void		*window;
	t_image		buffer;
	int			pressed_keys;
}	t_state;

#endif

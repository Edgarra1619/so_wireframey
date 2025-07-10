/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:44:13 by edgribei          #+#    #+#             */
/*   Updated: 2025/07/10 16:44:45 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>
#include <mlx.h>
#include <my_math.h>
#include <render.h>
#include <state.h>
#include <unistd.h>
#include <vector.h>
#include <X11/keysym.h>

int	render_hook(t_state *state)
{
	static int	count;

	update_camera_rot(&state->camera);
	if (state->pressed_keys & KEYCODEW)
		state->camera.pos = sum_vecf3(state->camera.pos, (t_vecf3)
			{state->camera.sin_rotx * 2, state->camera.cos_rotx * 2, 0});
	if (state->pressed_keys & KEYCODES)
		state->camera.pos = sum_vecf3(state->camera.pos, (t_vecf3)
			{-state->camera.sin_rotx * 2, -state->camera.cos_rotx * 2, 0});
	if (state->pressed_keys & KEYCODEA)
		state->camera.pos = sum_vecf3(state->camera.pos, (t_vecf3)
			{state->camera.cos_rotx * 2, -state->camera.sin_rotx * 2, 0});
	if (state->pressed_keys & KEYCODED)
		state->camera.pos = sum_vecf3(state->camera.pos, (t_vecf3)
			{-state->camera.cos_rotx * 2, state->camera.sin_rotx * 2, 0});
	if (state->pressed_keys & KEYCODEQ)
		state->camera.pos.z += 10;
	if (state->pressed_keys & KEYCODEE)
		state->camera.pos.z -= 10;
	clear_image(&state->buffer);
	count = (count + 1) % (state->mapcount * DELAY);
	render_map(&state->buffer, state->maps + count / DELAY,
		&state->camera, state->pre_map);
	mlx_put_image_to_window(state->mlx, state->window, state->buffer.ptr, 0, 0);
	return (0);
}

#ifndef BONUS

int	keyboard_down_hook(int keycode, t_state *state)
{
	if (keycode == 0xFF1B)
		mlx_loop_end(state->mlx);
	return (0);
}

t_map	*parse_gif(const char *a, int *b)
{
	(void) a;
	(void) b;
	return (NULL);
}

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:44:10 by edgribei          #+#    #+#             */
/*   Updated: 2025/07/10 16:44:15 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <state.h>
#include <X11/keysym.h>
#include <math.h>
#include <my_math.h>

int	keyboard_up_hook(int keycode, t_state *state)
{
	if (keycode == XK_Escape)
		mlx_loop_end(state->mlx);
	if (keycode == 'w')
		state->pressed_keys &= ~KEYCODEW;
	if (keycode == 's')
		state->pressed_keys &= ~KEYCODES;
	if (keycode == 'a')
		state->pressed_keys &= ~KEYCODEA;
	if (keycode == 'd')
		state->pressed_keys &= ~KEYCODED;
	if (keycode == 'q')
		state->pressed_keys &= ~KEYCODEQ;
	if (keycode == 'e')
		state->pressed_keys &= ~KEYCODEE;
	return (0);
}

int	keyboard_down_hook(int keycode, t_state *state)
{
	if (keycode == 0xFF1B)
		mlx_loop_end(state->mlx);
	if (keycode == 'w')
		state->pressed_keys |= KEYCODEW;
	if (keycode == 's')
		state->pressed_keys |= KEYCODES;
	if (keycode == 'a')
		state->pressed_keys |= KEYCODEA;
	if (keycode == 'd')
		state->pressed_keys |= KEYCODED;
	if (keycode == 'q')
		state->pressed_keys |= KEYCODEQ;
	if (keycode == 'e')
		state->pressed_keys |= KEYCODEE;
	return (0);
}

//unused in bonus
int	mouse_up_hook(int button, t_vec3 pos, t_state *state)
{
	(void) pos;
	if (button == 1)
		state->pressed_keys &= ~BUTTONL;
	else if (button == 3)
		state->pressed_keys &= ~BUTTONR;
	else if (button == 4)
		state->camera.zoom *= 1.1;
	else if (button == 5)
		state->camera.zoom /= 1.1;
	return (0);
}

//unused in bonus
int	mouse_down_hook(int button, t_vec3 pos, t_state *state)
{
	if (button == 1)
		state->pressed_keys |= BUTTONL;
	else if (button == 3)
		state->pressed_keys |= BUTTONR;
	state->mouse_pos = (t_vec2){pos.x, pos.z};
	(void) pos;
	return (0);
}

int	mouse_move_hook(int posx, int posy, t_state *state)
{
	const t_vecf2	mov = (t_vecf2)
	{(float)(state->mouse_pos.x - posx) / 10,
		(float)(state->mouse_pos.y - posy) / 10};

	if (state->pressed_keys & BUTTONL)
		state->camera.vertical_scale
			= clampf(powf(1.1f, -mov.y) * state->camera.vertical_scale,
				0.1f, 10.0f);
	if (state->pressed_keys & BUTTONR)
		rotate_camera(&state->camera, mov);
	state->mouse_pos = (t_vec2){posx, posy};
	return (0);
}

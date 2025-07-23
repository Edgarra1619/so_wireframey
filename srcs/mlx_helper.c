/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:10:11 by edgribei          #+#    #+#             */
/*   Updated: 2025/07/10 17:10:18 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include <state.h>
#include <mlx.h>
#include <hooks.h>
#include <render.h>

#ifdef BONUS

static void	start_mlx_loop(t_state *state)
{
	mlx_hook(state->window, ButtonPress, ButtonPressMask, mouse_down_hook,
		state);
	mlx_hook(state->window, ButtonRelease, ButtonReleaseMask, mouse_up_hook,
		state);
	mlx_hook(state->window, MotionNotify, ButtonMotionMask, mouse_move_hook,
		state);
	mlx_hook(state->window, KeyPress, KeyPressMask, keyboard_down_hook,
		state);
	mlx_hook(state->window, KeyRelease, KeyReleaseMask, keyboard_up_hook,
		state);
	mlx_loop_hook(state->mlx, render_hook, state);
	mlx_hook(state->window, ClientMessage, LeaveWindowMask, mlx_loop_end,
		state->mlx);
	mlx_loop(state->mlx);
}

#else

static void	start_mlx_loop(t_state *state)
{
	state->camera.vertical_scale = 5;
	state->camera.rot = (t_vecf2){0, 0};
	set_camera(&(state->camera), state->maps);
	mlx_hook(state->window, KeyPress, KeyPressMask, keyboard_down_hook, state);
	mlx_loop_hook(state->mlx, render_hook, state);
	mlx_hook(state->window, ClientMessage, LeaveWindowMask, mlx_loop_end,
		state->mlx);
	mlx_loop(state->mlx);
}

#endif

// returns -1 if failed
int	safe_start_mlx(t_state *const state)
{
	state->mlx = mlx_init();
	if (!state->mlx)
		return (-1);
	state->window = mlx_new_window(state->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"c not yet my pp");
	if (!state->window)
		return (-1);
	state->buffer.ptr = mlx_new_image(state->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!state->buffer.ptr)
		return (-1);
	state->buffer.data
		= mlx_get_data_addr(state->buffer.ptr, &state->buffer.bpp,
			&state->buffer.sline, &state->buffer.endian);
	if (!state->buffer.data)
		return (-1);
	state->buffer.size = (t_vec2){WINDOW_WIDTH, WINDOW_HEIGHT};
	start_mlx_loop(state);
	return (0);
}

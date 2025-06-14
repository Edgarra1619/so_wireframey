#include <X11/X.h>
#include <gif_parse.h>
#include <hooks.h>
#include <libft.h>
#include <map.h>
#include <mlx.h>
#include <render.h>
#include <state.h>
#include <stdlib.h>

#ifdef BONUS
static void start_mlx_loop(t_state *state) {
	mlx_hook(state->window, ButtonPress, ButtonPressMask, mouse_down_hook, state);
	mlx_hook(state->window, ButtonRelease, ButtonReleaseMask, mouse_up_hook,
					state);
	mlx_hook(state->window, MotionNotify, Button3MotionMask, mouse_move_hook, state);
	mlx_hook(state->window, KeyPress, KeyPressMask, keyboard_down_hook, state);
	mlx_hook(state->window, KeyRelease, KeyReleaseMask, keyboard_up_hook, state);
	mlx_loop_hook(state->mlx, render_hook, state);
	mlx_hook(state->window, ClientMessage, LeaveWindowMask, mlx_loop_end,
					state->mlx);
	mlx_loop(state->mlx);
}
#else
static void start_mlx_loop(t_state *state) {
	mlx_hook(state->window, KeyPress, KeyPressMask, keyboard_down_hook, state);
	mlx_loop_hook(state->mlx, render_hook, state);
	mlx_hook(state->window, ClientMessage, LeaveWindowMask, mlx_loop_end,
					 state->mlx);
	mlx_loop(state->mlx);
}
#endif

// returns -1 if failed
int safe_start_mlx(t_state *const state)
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
	state->buffer.data =
			mlx_get_data_addr(state->buffer.ptr, &state->buffer.bpp,
							&state->buffer.sline, &state->buffer.endian);
	if (!state->buffer.data)
		return (-1);
	state->buffer.size = (t_vec2){WINDOW_WIDTH, WINDOW_HEIGHT};
	start_mlx_loop(state);
	return (0);
}


void free_state(t_state *const state)
{
	free_map((void **)state->pre_map);
	free_maps(state->maps, state->mapcount);
	if (state->mlx)
	{
		if (state->buffer.ptr)
			mlx_destroy_image(state->mlx, state->buffer.ptr);
		mlx_destroy_window(state->mlx, state->window);
		mlx_destroy_display(state->mlx);
		free(state->mlx);
	}
}

static void	error_out(t_state *const state, const char *const errmsg)
{
	free_state(state);
	ft_putendl_fd(errmsg, 2);
	exit(1);
}

int main(int argc, char **argv)
{
	t_state state;

	ft_bzero(&state, sizeof(state));
	state.camera.rot = (t_vecf2){45, 57};
	state.camera.zoom = 1;
	state.camera.vertical_scale = 5;
	if (argc != 2)
		error_out(&state, "Wrong number of arguments");
	state.maps = parse_gif(argv[1], &(state.mapcount));
	if (!state.mapcount)
		error_out(&state, "Error while parsing file (is the path correct?)");
	state.camera.pos =
			(t_vecf3){-state.maps->size.x / 2.0, -state.maps->size.y / 2.0, 0};
	if (pre_map_alloc(&state) == -1)
		error_out(&state, "Error while preparing");
	if (safe_start_mlx(&state))
		error_out(&state, "Something happened while opening window!");
	free_state(&state);
}

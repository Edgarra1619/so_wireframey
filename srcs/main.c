#include <mlx.h>
#include <stdlib.h>
#include <strings.h>
#include <state.h>
#include <render.h>
#include <map.h>
#include <hooks.h>
#include <X11/X.h>

int	main()
{
	t_state	state;

	//TODO put ft_bzero here
	bzero(&state, sizeof(state));
	state.camera.pos = (t_vec3) {0, 0, 0};
	state.camera.rot = (t_vec2) {45, 57};
	state.maph = 100;
	state.mapw = 100;
	state.buffer.size = (t_vec2) {WINDOW_WIDTH, WINDOW_HEIGHT};
	state.map = test_map(state.mapw, state.maph, &state);

	state.mlx = mlx_init();
	state.window = mlx_new_window(state.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "c not yet my pp");
	state.buffer.ptr = mlx_new_image(state.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	state.buffer.data = mlx_get_data_addr(state.buffer.ptr, &state.buffer.bpp, &state.buffer.sline, &state.buffer.endian);
	mlx_key_hook(state.window, keyboard_down_hook, &state);
	mlx_mouse_hook(state.window, mouse_hook, &state);
	mlx_hook(state.window, KeyPress, KeyPressMask, keyboard_down_hook, &state);
	mlx_hook(state.window, KeyRelease, KeyReleaseMask, keyboard_up_hook, &state);
	mlx_loop_hook(state.mlx, render_hook, &state);
	mlx_hook(state.window, ClientMessage, LeaveWindowMask, mlx_loop_end, state.mlx);
	mlx_loop(state.mlx);
	free_map((void **)state.map, state.mapw);
	free_map((void **)state.pre_map, state.mapw);
	free_map((void **)state.color_map, state.mapw);
	mlx_destroy_image(state.mlx, state.buffer.ptr);
	mlx_destroy_window(state.mlx, state.window);
	mlx_destroy_display(state.mlx);
	free(state.mlx);
}

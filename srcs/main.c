#include <mlx.h>
#include <stdlib.h>
#include <strings.h>
#include <state.h>
#include <render.h>
#include <map.h>
#include <hooks.h>
#include <X11/X.h>
#include <gif_parse.h>
#include <stdio.h>

t_state g_state = {0};

int	main(int argc, char **argv)
{
	t_state	state;

	//TODO put ft_bzero here
	bzero(&state, sizeof(g_state));
	state.camera.rot = (t_vec2) {45, 57};
	if (argc < 2)
		return (0);
	state.maps = parse_gif(argv[1], &(state.mapcount));
	pre_map_alloc(&state);
	printf("%d", state.mapcount);
	state.camera.pos = (t_vec3) {-state.maps->size.x / 2, -state.maps->size.y / 2, 0};
	state.mlx = mlx_init();
	state.window = mlx_new_window(state.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "c not yet my pp");
	state.buffer.ptr = mlx_new_image(state.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	state.buffer.data = mlx_get_data_addr(state.buffer.ptr, &state.buffer.bpp, &state.buffer.sline, &state.buffer.endian);
	state.buffer.size = (t_vec2){WINDOW_WIDTH, WINDOW_HEIGHT};
	mlx_key_hook(state.window, keyboard_down_hook, &state);
	mlx_mouse_hook(state.window, mouse_hook, &state);
	mlx_hook(state.window, KeyPress, KeyPressMask, keyboard_down_hook, &state);
	mlx_hook(state.window, KeyRelease, KeyReleaseMask, keyboard_up_hook, &state);
	mlx_loop_hook(state.mlx, render_hook, &state);
	mlx_hook(state.window, ClientMessage, LeaveWindowMask, mlx_loop_end, state.mlx);
	mlx_loop(state.mlx);
	free_map((void**) state.pre_map);
	free_maps(state.maps, state.mapcount);
	mlx_destroy_image(state.mlx, state.buffer.ptr);
	mlx_destroy_window(state.mlx, state.window);
	mlx_destroy_display(state.mlx);
	free(state.mlx);
}

#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <state.h>
#include <render.h>
#include <map.h>
#include <time.h>
#include <hooks.h>
#include <X11/X.h>

int	main()
{
	t_state	state;

	state.camera.pos = (t_vec3) {0, 0, 0};
	state.camera.rot = (t_vec2) {45, 57};
	state.maph = 1000;
	state.mapw = 1000;
	state.map = test_map(state.mapw, state.maph);
	srand(clock());

	state.mlx = mlx_init();
	mlx_do_key_autorepeatoff(state.mlx);
	state.window = mlx_new_window(state.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "c not yet my pp");
	state.buffer = mlx_new_image(state.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_key_hook(state.window, keyboard_down_hook, &state);
	mlx_mouse_hook(state.window, mouse_hook, &state);
	mlx_hook(state.window, KeyPress, KeyPressMask, keyboard_down_hook, &state);
	mlx_hook(state.window, KeyRelease, KeyReleaseMask, keyboard_up_hook, &state);
	mlx_loop_hook(state.mlx, render_hook, &state);
	mlx_hook(state.window, ClientMessage, LeaveWindowMask, mlx_loop_end, state.mlx);
	mlx_loop(state.mlx);
	free_map(state.map, state.mapw);
	mlx_destroy_image(state.mlx, state.buffer);
	mlx_destroy_window(state.mlx, state.window);
	mlx_destroy_display(state.mlx);
	free(state.mlx);
}

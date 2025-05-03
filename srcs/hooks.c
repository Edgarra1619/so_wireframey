#include <vector.h>
#include <mlx.h>
#include <state.h>
#include <render.h>
#include <my_math.h>
#include <math.h>
#include <unistd.h>

int	render_hook(t_state *state)
{
//	write(2, "render", 6);
	put_square(state->buffer, (t_vec2){0, 0}, (t_vec2){WINDOW_WIDTH, WINDOW_HEIGHT}, (t_color) BLACK);
	render_map(state->buffer, state);
	mlx_put_image_to_window(state->mlx, state->window, state->buffer, 0, 0);
	return (0);
}

int	keyboard_hook(int keycode, t_state *state)
{
	const int	cosmove = cos((float) state->camera.rot.x / 180 * M_PI) * 10;
	const int	sinmove = sin((float) state->camera.rot.x / 180 * M_PI) * 10;
	if (keycode == 0xFF1B)
		mlx_loop_end(state->mlx);
	if (keycode == 'i')
		state->camera.rot.y = clamp(state->camera.rot.y + 10, 0, 90);
	if (keycode == 'k')
		state->camera.rot.y = clamp(state->camera.rot.y - 10, 0, 90);
	if (keycode == 'j')
		state->camera.rot.x = (state->camera.rot.x + 10) % 360;
	if (keycode == 'l')
		state->camera.rot.x = (state->camera.rot.x - 10) % 360;
	if (keycode == 'w')
		state->camera.pos = sum_vec3(state->camera.pos, (t_vec3) {sinmove,
				cosmove, 0});
	if (keycode == 's')
		state->camera.pos = sum_vec3(state->camera.pos, (t_vec3) {-sinmove,
				-cosmove, 0});
	if (keycode == 'a')
		state->camera.pos = sum_vec3(state->camera.pos, (t_vec3) {cosmove,
				-sinmove, 0});
	if (keycode == 'd')
		state->camera.pos = sum_vec3(state->camera.pos, (t_vec3) {-cosmove,
				sinmove, 0});
	if (keycode == 'q')
		state->camera.pos.z += 10;
	if (keycode == 'e')
		state->camera.pos.z -= 10;
	render_hook(state);
	return (0);
}

int	mouse_hook(int button, t_vec2 pos, t_state *state)
{
	(void) button;
	(void) pos;
	(void) state;
	return (0);
}


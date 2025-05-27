#include <vector.h>
#include <mlx.h>
#include <state.h>
#include <render.h>
#include <my_math.h>
#include <math.h>
#include <unistd.h>
#include <map.h>

static inline void	put_pixel_image(t_image *const image, const t_vec2 position, const t_color color)
{
	if (position.x < 0 || position.y < 0 ||
			position.x >= WINDOW_WIDTH || position.y >= WINDOW_HEIGHT)
		return ;
	((int*) (image->data + position.y * image->sline))[position.x] = color.color;
}

int	render_hook(t_state *state)
{
	const int	cosmove = cos((float) state->camera.rot.x / 180.0 * M_PI) * 2;
	const int	sinmove = sin((float) state->camera.rot.x / 180.0 * M_PI) * 2;
	static int	count;

	if (state->pressed_keys & KEYCODEW)
		state->camera.pos = sum_vec3(state->camera.pos, (t_vec3) {sinmove,
				cosmove, 0});
	if (state->pressed_keys & KEYCODES)
		state->camera.pos = sum_vec3(state->camera.pos, (t_vec3) {-sinmove,
				-cosmove, 0});
	if (state->pressed_keys & KEYCODEA)
		state->camera.pos = sum_vec3(state->camera.pos, (t_vec3) {cosmove,
				-sinmove, 0});
	if (state->pressed_keys & KEYCODED)
		state->camera.pos = sum_vec3(state->camera.pos, (t_vec3) {-cosmove,
				sinmove, 0});
	if (state->pressed_keys & KEYCODEQ)
		state->camera.pos.z += 10;
	if (state->pressed_keys & KEYCODEE)
		state->camera.pos.z -= 10;
//	put_square(&state->buffer, (t_vec2){0, 0}, (t_vec2){WINDOW_WIDTH, WINDOW_HEIGHT}, (t_color) BLACK);
	clear_image(&state->buffer);
	count = (count + 1) % (state->mapcount * DELAY);
	render_map(&state->buffer, state->maps + count / DELAY, &state->camera, state->pre_map);
	mlx_put_image_to_window(state->mlx, state->window, state->buffer.ptr, 0, 0);
	return (0);
}

int	keyboard_up_hook(int keycode, t_state *state)
{
	if (keycode == 0xFF1B)
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
	if (keycode == 'i')
		state->camera.rot.y = clamp(state->camera.rot.y + 10, 0, 90);
	if (keycode == 'k')
		state->camera.rot.y = clamp(state->camera.rot.y - 10, 0, 90);
	if (keycode == 'j')
		state->camera.rot.x = (state->camera.rot.x + 10) % 360;
	if (keycode == 'l')
		state->camera.rot.x = (state->camera.rot.x - 10) % 360;
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

int	mouse_hook(int button, t_vec2 pos, t_state *state)
{
	(void) button;
	(void) pos;
	(void) state;
	return (0);
}


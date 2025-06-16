#include <map.h>
#include <math.h>
#include <mlx.h>
#include <my_math.h>
#include <render.h>
#include <state.h>
#include <stdio.h>
#include <unistd.h>
#include <vector.h>
#include <X11/keysym.h>

void	update_camera_rot(t_camera *const camera)
{
	camera->sin_rotx = sin((float) camera->rot.x / 180.0 * M_PI);
	camera->cos_rotx = cos((float) camera->rot.x / 180.0 * M_PI);
	camera->sin_roty = sin((float) camera->rot.y / 180.0 * M_PI);
	camera->cos_roty = cos((float) camera->rot.y / 180.0 * M_PI);
}

void	rotate_camera(t_camera *const camera, t_vecf2 rotation)
{
	camera->rot.y = clampf(camera->rot.y - rotation.y, 0, 90);
	camera->rot.x = camera->rot.x + rotation.x;
	if (camera->rot.x < 0)
		camera->rot.x += 360;
	if (camera->rot.x > 360)
		camera->rot.x -= 360;
	update_camera_rot(camera);
}

int	render_hook(t_state *state)
{
	static int	count;

	update_camera_rot(&state->camera);
	if (state->pressed_keys & KEYCODEW)
		state->camera.pos = sum_vecf3(state->camera.pos, (t_vecf3) {state->camera.sin_rotx * 2,
				state->camera.cos_rotx * 2, 0});
	if (state->pressed_keys & KEYCODES)
		state->camera.pos = sum_vecf3(state->camera.pos, (t_vecf3) {-state->camera.sin_rotx,
				-state->camera.cos_rotx, 0});
	if (state->pressed_keys & KEYCODEA)
		state->camera.pos = sum_vecf3(state->camera.pos, (t_vecf3) {state->camera.cos_rotx,
				-state->camera.sin_rotx, 0});
	if (state->pressed_keys & KEYCODED)
		state->camera.pos = sum_vecf3(state->camera.pos, (t_vecf3) {-state->camera.cos_rotx,
				state->camera.sin_rotx, 0});
	if (state->pressed_keys & KEYCODEQ)
		state->camera.pos.z += 10;
	if (state->pressed_keys & KEYCODEE)
		state->camera.pos.z -= 10;
	clear_image(&state->buffer);
	count = (count + 1) % (state->mapcount * DELAY);
	render_map(&state->buffer, state->maps + count / DELAY, &state->camera, state->pre_map);
	mlx_put_image_to_window(state->mlx, state->window, state->buffer.ptr, 0, 0);
	return (0);
}

//unused in bonus
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

#ifdef BONUS
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
# else
int	keyboard_down_hook(int keycode, t_state *state)
{
	if (keycode == 0xFF1B)
		mlx_loop_end(state->mlx);
	return (0);
}

#endif

//unused in bonus
int	mouse_up_hook(int button, t_vec3 pos, t_state *state)
{
	(void) pos;
	if(button == 5)
		state->camera.zoom /= 1.1;
	if(button == 4)
		state->camera.zoom *= 1.1;
	printf("%d %d %d %d up\n", button, pos.x, pos.y, pos.z);
	return (0);
}

//unused in bonus
int	mouse_down_hook(int button, t_vec3 pos, t_state *state)
{
	if (button == 3)
		state->mouse_pos = (t_vec2) {pos.x, pos.z};
	(void) pos;
	printf("%d down\n", button);
	return (0);
}

int	mouse_move_hook(int posx, int posy, t_state *state)
{
	const t_vecf2	mov = (t_vecf2)
		{(float) (state->mouse_pos.x - posx) / 10,
		(float)(state->mouse_pos.y - posy) / 10};

	rotate_camera(&state->camera, mov);
	state->mouse_pos = (t_vec2) {posx, posy};
	return(0);
}

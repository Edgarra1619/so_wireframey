#include <vector.h>
#include <mlx.h>
#include <state.h>
#include <X11/X.h>

int	keyboard_hook(int keycode, t_state *state)
{
	if (keycode == 'q')
		mlx_loop_end(state->mlx);
	return (0);
}

int	mouse_hook(int button, t_vec2 pos, t_state *state)
{
	(void) button;
	(void) pos;
	(void) state;
	return (0);
}

int	render_hook(t_state *state)
{
	(void) state;
	return (0);
}

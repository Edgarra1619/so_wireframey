#ifndef HOOKS_H
# define HOOKS_H
# include <state.h>

int	mouse_down_hook(int button, t_vec3 pos, t_state *state);
int	mouse_up_hook(int button, t_vec3 pos, t_state *state);
int	mouse_move_hook(int button, t_vec3 pos, t_state *state);
int	keyboard_down_hook(int keycode, t_state *state);
int	keyboard_up_hook(int keycode, t_state *state);
int	render_hook(t_state *state);

#endif

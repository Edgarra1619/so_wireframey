#ifndef INPUT_H
# define INPUT_H
int	mouse_hook(int button, t_vec2 pos, t_state *state);
int	keyboard_hook(int keycode, t_state *state);
int	render_hook(t_state *state);
#endif

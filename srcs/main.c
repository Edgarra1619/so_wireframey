#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <state.h>
#include <render.h>
#include <map.h>
#include <time.h>

void	input_hook(void)
{



}

int	main()
{
	char	str[10];
	void	*mlx;
	void	*window;
	void	*buffer;
	t_state	state;

	state.camera.position = (t_vec2) {0, 0};
	state.camera.rotation = (t_vec2) {0, 0};
	state.map = test_map(&state.mapw, &state.maph);
	srand(clock());

	t_vec2	start;
	t_vec2	end;

	start.x = 10;
	start.y = 10;

	end.x = 400;
	end.y = 300;
	//	t_state state;
	mlx = mlx_init();
	window = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "c not yet my pp");
	buffer = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	render_map(buffer, &state);
	mlx_put_image_to_window(mlx, window, buffer, 0, 0);
	//mlx_key_hook(window, int (*funct_ptr)(), void *param);
	//mlx_mouse_hook(window, int (*funct_ptr)(), void *param)
	read(0, str, 3);
	free_map(state.map, state.mapw);
	mlx_destroy_image(mlx, buffer);
	mlx_destroy_window(mlx, window);
	mlx_destroy_display(mlx);
	free(mlx);
}

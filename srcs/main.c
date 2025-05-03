#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <state.h>
#include <render.h>

void	input_hook(void)
{



}

int	main()
{
	char	str[10];
	void	*mlx;
	void	*window;
	void	*buffer;
	t_vec2	start;
	t_vec2	end;

	start.x = 10;
	start.y = 10;

	end.x = 400;
	end.y = 300;
	//	t_state state;
	mlx = mlx_init();
	window = mlx_new_window(mlx, 640, 360, "HELLO");
	buffer = mlx_new_image(mlx, 640, 360);
	put_square(buffer, start, end, (t_color) 0xFFFF20FF);
	put_line(buffer, start, end, (t_color) 0xFF000000);
	mlx_put_image_to_window(mlx, window, buffer, 0, 0);
	//mlx_key_hook(window, int (*funct_ptr)(), void *param);
	//mlx_mouse_hook(window, int (*funct_ptr)(), void *param)
	read(0, str, 3);
	mlx_destroy_image(mlx, buffer);
	mlx_destroy_window(mlx, window);
	mlx_destroy_display(mlx);
	free(mlx);
}

#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <draw_utils.h>

int	main()
{
//	char	str[10];
	void	*mlx;
	void	*window;
	t_vec2 a;
	t_vec2 b;

	a.x = 40;
	a.y = 40;
	b.x = 10;
	b.y = 20;
	mlx = mlx_init();
	window = mlx_new_window(mlx, 160, 90, "HELLO");
	draw_line(mlx, window, a,b, 0xFFFF0000);
	mlx_loop(mlx);
//	read(0, str, 3);
	mlx_destroy_window(mlx, window);
	mlx_destroy_display(mlx);
	free(mlx);
}

#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>

int	main()
{
	char	str[10];
	void	*mlx;
	void	*window;
	

	mlx = mlx_init();
	window = mlx_new_window(mlx, 160, 90, "HELLO");

	read(0, str, 3);
	mlx_destroy_window(mlx, window);
	mlx_destroy_display(mlx);
	free(mlx);
}

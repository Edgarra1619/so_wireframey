#include <mlx.h>
#include <draw_utils.h>

void	draw_line(void *mlx_ptr, void *win_ptr, t_vec2 a, t_vec2 b, int color)
{
	float	m;
	int	k;
	int	i;
	int	max;

	if(a.x != b.x)
	{
		m = (float) (b.y - a.y) / (b.x - a.x);
		k = a.y - m * a.x;
		i = (a.x * (a.x < b.x)) + (b.x * (b.x < a.x));
		max = (a.x * (a.x > b.x)) + (b.x * (b.x > a.x));
		while (i++ < max)
			mlx_pixel_put(mlx_ptr, win_ptr, i, i * m + k, color);
	}
	else if (a.y != b.y)
	{
		m = (float) (b.x - a.x) / (b.y - a.y);
		k = a.x - m * a.y;
		i = (a.y * (a.y < b.y)) + (b.y * (b.y < a.y));
		max = (a.y * (a.y > b.y)) + (b.y * (b.y > a.y));
		while (i++ < max)
			mlx_pixel_put(mlx_ptr, win_ptr, i * m + k, i, color);
	}
	mlx_pixel_put(mlx_ptr, win_ptr, a.x, a.y, color);
}


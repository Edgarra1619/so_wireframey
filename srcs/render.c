#include <vector.h>
#include <mlx.h>

static inline void	put_pixel_image(char *image, int sline, int x, int y, int color)
{
	((int*) (image + y * sline))[x] = color;
}
void	put_square(void *image, t_vec2 UL, t_vec2 DR, int color)
{
	int	x;
	int	sline;
	char	*bits;

	bits = mlx_get_data_addr(image, &x, &sline, &x);
	while (UL.y <= DR.y)
	{
		x = UL.x;
		while (x <= DR.x)
		{
			put_pixel_image(bits, sline, x, UL.y, color);
			x++;
		}
		UL.y++;
	}
}

// y = mx + b
void	put_line(void *image, t_vec2 start, t_vec2 end, int color)
{
	float	m;
	int	x;
	int	max;

	m = (float)(end.y - start.y) / (float)(end.x - start.x);
	if (start.x != end.x)
	{
		x = (start.x * (start.x < end.x)) + (end.x * (end.x < start.x));
		max = (start.x * (start.x > end.x)) + (end.x * (end.x > start.x));
		while (x < max)
		{
			
			i++;
		}


	}





}

#ifndef DRAW_UTILS_H
# define DRAW_UTILS_H


typedef struct s_vec2
{
	int	x;
	int	y;
}	t_vec2;


void	draw_line(void *mlx_ptr, void *win_ptr, t_vec2 a, t_vec2 b, int color);


#endif

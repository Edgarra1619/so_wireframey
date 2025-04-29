#ifndef RENDER_H
# define RENDER_H
# include <vector.h>
void	put_square(void *image, t_vec2 UL, t_vec2 DR, int color);
void	put_line(void *image, t_vec2 a, t_vec2 b, int color);
void	put_pixel_image(char *image, int sline, int x, int y, int color);
#endif

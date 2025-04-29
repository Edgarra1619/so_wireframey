#ifndef COLOR_H
# define COLOR_H

enum	std_colors
{
	RED = 0xFFFF0000,
	GREEN = 0xFF00FF00,
	BLUE = 0xFF0000FF,
	WHITE = 0xFFFFFFFF,
	BLACK = 0xFF000000,
};

typedef union u_color
{
	unsigned int	color;
	struct
	{
		unsigned char	a;
		unsigned char	r;
		unsigned char	g;
		unsigned char	b;
	}	rgba;
} t_color;

#endif

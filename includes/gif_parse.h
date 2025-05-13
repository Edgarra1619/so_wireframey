#ifndef GIF_PARSE_H
# define GIF_PARSE_H

# include <stdint.h>
typedef struct	s_gif_header
{
	char	signature[3];
	char	version[3];
	int16_t	screen_width;
	int16_t	screen_height;
	char	packed;
	char	_ignored[2];
}	t_gif_header;

#endif

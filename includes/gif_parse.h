#ifndef GIF_PARSE_H
# define GIF_PARSE_H
# include <map.h>
# include <stdint.h>

typedef struct	s_gif_header
{
	char	signature[3];
	char	version[3];
	uint16_t	screen_width;
	uint16_t	screen_height;
	char	packed;
	char	_ignored[2];
}	t_gif_header;

//if prev code is -1, it's a core code
//if last_index is -1, it isn't initialized
//if prev_code is itself, then it's a clear code
typedef struct	s_code
{
	int	prev_code;
	int	last_index;
} t_code;

typedef struct	s_ctable
{
	int			prev_code;
	char		code_size;
	char		lzw;
	t_code		*table;
} t_ctable;

typedef struct		s_gifmap
{
	t_map			*map;
	int				offset;
	const t_color	*cltab;
}					t_gifmap;

t_map	*parse_gif (const char *path, int *image_count);
char parse_imgdata(char lzw, int fd, t_gifmap *map);
#endif

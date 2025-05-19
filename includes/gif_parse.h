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


//the branches should be a list, when using this as a general case
//however, this is for the gif
typedef struct	s_giftree
{
	struct s_giftree	*branches[255];
	int					content;
}	t_giftree;

//if prev code is -1, it's a core code
//if last_index is -1, it isn't initialized
typedef struct	s_code
{
	int	prev_code;
	int	last_index;
} t_code;


typedef struct	s_ctable
{
	int			prev_code;
	char		code_size;
	int			clear_code;
	t_code		*table;
} t_ctable;

t_giftree	*start_tree(int ct_size);
#endif

#ifndef PARSE_H
# define PARSE_H
# include <color.h>
# include <state.h>

typedef struct	s_heicol
{
	int		height;
	t_color	color;
}	t_heicolor;
int	parse_file(const char *path, t_state *state);


#endif

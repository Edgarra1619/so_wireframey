#include <state.h>
#include <gif_parse.h>
























//return-1 on error
int	parse_file(const char *path, t_state *state)
{
	state->maps = parse_gif(path, &(state->mapcount));
	if(state->maps)



	return (0);
}

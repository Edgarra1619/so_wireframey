#include <errno.h>
#include <fcntl.h>
#include <libft.h>
#include <state.h>
#include <stdlib.h>
#include <gif_parse.h>
#include <parse.h>
#include <unistd.h>


t_map	*parse_lines(t_list *lines)
{
	t_map *const	map = ft_calloc(sizeof(t_map), 1);
	t_list			*temp;

	if (!map)
		return (NULL);
	map->size = (t_vec2) {
		ft_count_words(lines->content, ' '), ft_lstsize(lines)};
	if (new_map(map))
	{
		free(map);
		return (NULL)
	}
	while (lines)
	{


	}
	return (map);
}

t_list	*read_all_lines(const int fd)
{
	t_list	*lines;
	char	*content;
	t_list	*new;

	lines = NULL;
	content = get_next_line(fd);
	while (content)
	{
		new = ft_lstnew(content);
		if (!new)
		{
			free(content);
			ft_lstclear(&lines, free);
			return (NULL);
		}
		ft_lstadd_back(&lines, new);
		content = get_next_line(fd);
		if (errno && !content)
		{
			ft_lstclear(&lines, free);
			return (NULL);
		}
	}
	return (lines);
}

t_map	*parse_map_file(const char *path)
{
	const int	fd = open(path, O_RDONLY);
	t_list		*lines;
	t_map		*map;

	if (fd < 0)
	{
		close(fd);
		return (NULL);
	}
	lines = read_all_lines(fd);
	map = parse_lines(lines); 
	ft_lstclear(&lines, free);
	close(fd);
	return (map);
}

#ifndef BONUS

t_map	*parse_gif(const char *a, int *b)
{
	(void) a;
	(void) b;
	return (NULL);
}

#endif

//return-1 on error
int	parse_file(const char *path, t_state *state)
{
	state->maps = parse_gif(path, &(state->mapcount));
	if (state->maps)
		return (0);
	return (0);
}

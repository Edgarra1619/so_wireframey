#include <errno.h>
#include <fcntl.h>
#include <libft.h>
#include <state.h>
#include <stdlib.h>
#include <gif_parse.h>
#include <parse.h>

void	parse_line(void **line)
{
	t_heicolor	*const parsed_line =
		ft_calloc(ft_count_words(*line, ' ') + 1, sizeof(t_heicolor));

	//TODO expose count_words from split
	if(!parsed_line)
	{
		free(*line);
		*line = NULL;
		return ;
	}
	while ()

	free(*line);
	*line = parsed_line;
}

t_list	*read_all_lines(const int fd)
{
	t_list	*lines;
	char	*content;
	t_list	*new;

	lines = NULL;
	//TODO import gnl to libft
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
	t_list		*temp;
	t_map		*map;

	if (fd < 0 || !map)
	{
		free(map);
		return (NULL);
	}
	lines = read_all_lines(fd);
	while (lines)
	{
		temp = lines->next;
		parse_line(&(lines->content));
		lines = temp;
	}
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

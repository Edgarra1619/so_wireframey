#include <color.h>
#include <gif_parse.h>
#include <map.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void	parse_color_table(t_color table[256], int size, int fd)
{
	int	i;

	i = 0;
	while (i < size)
	{
		read(fd, table + i, 3);
		i++;
	}
}

t_gif_header	parse_header(int fd)
{
	t_gif_header	info;
	
	read(fd, &info, sizeof(info));
	return (info);
}

//TODO parse 87a
//TODO parse 89a = parse 87a but skip the extensions
t_map	*parse_gif(const char *path)
{
	const int	fd = open(path, O_RDONLY);
	t_gif_header	info;
	t_map		*map;
	t_color		color_table[256];

	if (fd < 0)
		return (NULL);
	info = parse_header(fd);
	// TODO put ft_strcmp and ft_calloc here
	if (strncmp(info.signature, "GIF", 3))
	{
		close(fd);
		return (NULL);
	}
	
	map = calloc(sizeof(t_map), 1);
	if (!map)
	{
		close(fd);
		return (NULL);
	}
	close (fd);
	return (map);
}

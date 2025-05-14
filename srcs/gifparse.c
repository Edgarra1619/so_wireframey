#include <color.h>
#include <gif_parse.h>
#include <map.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void	parse_color_table(t_color *table, int size, int fd)
{
	int	i;

	i = 0;
	while (i < size)
	{
		read(fd, table + i, 3);
		i++;
	}
}

void	parse_image(t_color *table, int size, int fd)
{
	t_giftree	




}

t_gif_header	parse_header(int fd)
{
	t_gif_header	info;
	
	read(fd, &info, sizeof(info));
	return (info);
}

//TODO parse 87a
//TODO parse 89a = parse 87a but skip the extensions
t_map	*parse_gif(const char *path, int *image_count)
{
	const int	fd = open(path, O_RDONLY);
	t_gif_header	info;
	t_color		g_coltable[256];

	*image_count = 0;
	if (fd < 0)
		return (NULL);
	info = parse_header(fd);
	// TODO put ft_strcmp and ft_calloc here
	if (strncmp(info.signature, "GIF", 3))
	{
		close(fd);
		return (NULL);
	}
	if (info.packed & 0b1000000)
		parse_color_table(g_coltable, 1 << ((info.packed & 0b0111) + 1), fd);
	close (fd);
	return (map);
}

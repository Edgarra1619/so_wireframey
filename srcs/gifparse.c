#include <color.h>
#include <gif_parse.h>
#include <map.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


void	add_to_map(t_gifmap *map, t_color color)
{
	map->map->color_map[map->offset.x][map->offset.y] = color;
	map->map->height_map[map->offset.x][map->offset.y] = 
		color.s_rgba.r + color.s_rgba.g + color.s_rgba.b;
	map->offset.x++;
	if (map->offset.x == map->map->size.x)
	{
		map->offset.x = 0;
		map->offset.y++;
	}
}

//returns what got overflowed
int	bitshift_left(const size_t shift, char *data, size_t size)
{
	const size_t		byte_shift = size / 8;
	const char	mask = 255 << (8 - (shift % 8));
	size_t				i;
	int					result;

	i = 0;
	result = data[0] * byte_shift;
	while (i < size)
	{
		if (i < size - byte_shift)
			data[i] = data[i + byte_shift];
		else
			data[i] = 0;
		i++;
	}
	size -= byte_shift;
	i = 0;
	result |= data[0] & mask >> (8 - (shift % 8));
	while (i < size - 1)
	{
		data[i] = (data[i] << (shift % 8)) |
			((data[i + 1] & mask) >> (8 - (shift % 8)));
		i++;
	}
	data[size] = data[size] << (shift % 8);
	return (result);
}

//called after the image separator byte (2C)
t_map	*parse_image(t_color *table, int size, int fd)
{
	t_gifmap	map;
	char		lzw;
	int16_t		size[2];

	//skip the image alignment and ignore it
	read(fd, size, 4);
	//TODO parse size and create a map to pass to parse block
	read(fd, size, 4);
	read(fd, &lzw, 1);
	while (parse_block(lzw, fd, map))
		;

}

t_gif_header	parse_header(int fd)
{
	t_gif_header	info;
	
	read(fd, &info, sizeof(info));
	return (info);
}

void	parse_color_table(t_color *const table, const int size, const int fd)
{
	int	i;

	i = 0;
	while (i < size)
	{
		read(fd, table + i, 3);
		i++;
	}
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

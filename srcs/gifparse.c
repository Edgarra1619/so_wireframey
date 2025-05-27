#include "vector.h"
#include <color.h>
#include <gif_parse.h>
#include <map.h>
#include <fcntl.h>
#include <stdint.h> //various int types
#include <string.h> //memset
#include <unistd.h> //read comes here
#include <stdlib.h> //mallocs and frees and such
#include <libft.h> //the list functions

void	parse_color_table(t_color *const table, const int size, const int fd);

//called after the image separator byte (2C)
//does not accept interlacing
t_map	*parse_image(t_color *table, int fd,
		const unsigned char *const gctrl, t_list *const fmap)
{
	t_gifmap		map;
	char			lzw;
	uint16_t		size[2];
	t_color			coltable[256];

	map.offset = 0;
	map.map = malloc(sizeof(t_map));
	if(fmap)
		map.fmap = fmap->content;
	map.cltab = table;
	//skip the image alignment and ignore it
	read(fd, size, 4);
	map.map->position = (t_vec2) {size[0], size[1]};
	//TODO parse size and create a map to pass to parse block
	read(fd, size, 4);
	map.map->size.x = size[0];
	map.map->size.y = size[1];
	new_map(map.map);
	read(fd, &lzw, 1);
	if (lzw & 0b10000000)
	{
		parse_color_table(coltable, (int) 1 << ((lzw & 0b0111) + 1), fd);
		map.cltab = coltable;
	}
	if (gctrl[0] & 1)
		map.cltab[gctrl[3]].s_rgba.a = 0;
	read(fd, &lzw, 1);
	parse_imgdata(lzw, fd, &map);
	map.cltab[gctrl[3]].s_rgba.a = 0;
	return (map.map);
}

t_gif_header	parse_header(int fd)
{
	t_gif_header	info;

	read(fd, &info, 13);
	return (info);
}

void	parse_color_table(t_color *const table, const int size, const int fd)
{
	int	i;

	i = 0;
	while (i < size)
	{
		table[i].color = 0xFFFFFFFF;
		read(fd, &table[i].s_rgba.r, 1);
		read(fd, &table[i].s_rgba.g, 1);
		read(fd, &table[i].s_rgba.b, 1);
		i++;
	}
}

void	skip_blockdata(const int fd)
{
	char	buffer[256];

	read(fd, buffer, 1);
	while (*buffer)
	{
		read(fd, buffer, *buffer);
		read(fd, buffer, 1);
	}
}

void	skip_extensions(const int fd, unsigned char *const gctrl)
{
	unsigned char	buffer[256];

	read(fd, buffer, 1);
	if (*buffer == 0xF9)
	{
		read(fd, buffer, 1);
		read(fd, gctrl, 4);
	}
	else if (*buffer == 0xFE || *buffer == 0x01 || *buffer == 0xFF)
		skip_blockdata(fd);
}

t_map	*parse_allimg(const int fd, int *image_count,
		t_color *const cltab)
{
	t_list	*list_maps;
	t_list	*temp;
	t_map	*array;
	unsigned char	buffer[5];
	int		i;

	ft_bzero(buffer, 5);
	read(fd, buffer, 1);
	list_maps = NULL;
	while (buffer[0] != 0x3B)
	{
		if(buffer[0] == 0x21)
			skip_extensions(fd, buffer + 1);
		if (buffer[0] == 0x2C)
			ft_lstadd_back(&list_maps,
					ft_lstnew(parse_image(cltab, fd, buffer + 1, list_maps)));
		read(fd, buffer, 1);
	}
	*image_count = ft_lstsize(list_maps);
	array = malloc(sizeof(t_map) * (*image_count));
	i = 0;
	while (list_maps)
	{
		temp = list_maps->next;
		array[i++] = *((t_map *) list_maps->content);
		ft_lstdelone(list_maps, free);
		list_maps = temp;
	}
	return (array);
}

//TODO parse 87a
//TODO parse 89a = parse 87a but skip the extensions
t_map	*parse_gif(const char *path, int *image_count)
{
	const int	fd = open(path, O_RDONLY);
	t_gif_header	info;
	t_color		glob_coltable[256];
	t_map		*maps;

	*image_count = 0;
	if (fd < 0)
	{
		write(2, "COULDN'T OPEN FILE\n", 19);
		return (NULL);
	}
	info = parse_header(fd);
	// TODO put ft_strcmp and ft_calloc here
	if (ft_strncmp(info.signature, "GIF", 3) || !(info.version[0] == '8'))
	{
		write(2, "THIS IS NOT A GIF\n", 18);
		close(fd);
		return (NULL);
	}
	if(info.packed & 0b10000000)
		parse_color_table(glob_coltable, (int) 1 << ((info.packed & 0b0111) + 1), fd);
	maps = parse_allimg(fd, image_count, glob_coltable);
	close (fd);
	return (maps);
}

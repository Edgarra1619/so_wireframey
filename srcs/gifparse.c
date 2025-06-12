#include "vector.h"
#include <color.h>
#include <fcntl.h>
#include <gif_parse.h>
#include <libft.h> //the list functions
#include <map.h>
#include <stdint.h> //various int types
#include <stdlib.h> //mallocs and frees and such
#include <unistd.h> //read comes here

t_color *parse_color_table(t_color *const table, const int size, const int fd);

// called after the image separator byte (2C)
// does not accept interlacing
t_map *parse_image(t_color *table, int fd, const unsigned char *const gctrl,
                   t_list *const fmap)
{
	t_gifmap	map;
	uint16_t	size[5];
	t_color		coltable[256];

	map.offset = 0;
	map.map = malloc(sizeof(t_map));
	if (!map.map)
		return (NULL);
	map.cltab = table;
	read(fd, size, 9);
	map.map->position = (t_vec2){size[0], size[1]};
	map.map->size = (t_vec2){size[2], size[3]};
	if (!copy_map(map.map, fmap))
		return (NULL);
	if (*((char *)(size + 4)) & 0b10000000)
		map.cltab = parse_color_table(coltable,
			(int)1 << ((*((char *)(size + 4)) & 0b0111) + 1), fd);
	if (gctrl[0] & 1)
		map.cltab[gctrl[3]].a = 0;
	read(fd, ((char*)size) + 9, 1);
	parse_imgdata(((char*)size)[9], fd, &map);
	if (fmap)
		map.map->size = ((t_map *)fmap->content)->size;
	return (map.map);
}

t_gif_header parse_header(int fd) {
	t_gif_header info;

	read(fd, &info, 13);
	return (info);
}

t_color *parse_color_table(t_color *const table, const int size, const int fd) {
	int i;

	i = 0;
	while (i < size) {
		table[i].color = 0xFFFFFFFF;
		read(fd, &table[i].r, 1);
		read(fd, &table[i].g, 1);
		read(fd, &table[i].b, 1);
		i++;
	}
	return (table);
}

void skip_blockdata(const int fd) {
	char buffer[256];

	read(fd, buffer, 1);
	while (*buffer) {
		read(fd, buffer, *buffer);
		read(fd, buffer, 1);
	}
}

void skip_extensions(const int fd, unsigned char *const gctrl) {
	unsigned char buffer[256];

	read(fd, buffer, 1);
	if (*buffer == 0xF9) {
		read(fd, buffer, 1);
		read(fd, gctrl, 4);
		read(fd, buffer, 1);
	} else if (*buffer == 0xFE || *buffer == 0x01 || *buffer == 0xFF)
		skip_blockdata(fd);
}

t_map *parse_allimg(const int fd, int *image_count, t_color *const cltab)
{
	t_list *list_maps;
	t_list *temp;
	t_map *array;
	unsigned char buffer[5];
	int i;

	ft_bzero(buffer, 5);
	read(fd, buffer, 1);
	list_maps = NULL;
	while (buffer[0] != 0x3B) {
		if (buffer[0] == 0x21)
			skip_extensions(fd, buffer + 1);
		else if (buffer[0] == 0x2C)
			//TODO guard this
			ft_lstadd_back(&list_maps,
				 ft_lstnew(parse_image(cltab, fd, buffer + 1, ft_lstlast(list_maps))));
		else
		{
			ft_lstclear(&list_maps, free);
			return (NULL);
		}
		read(fd, buffer, 1);
	}
	*image_count = ft_lstsize(list_maps);
	//TODO guard this
	array = malloc(sizeof(t_map) * (*image_count));
	i = 0;
	while (list_maps) {
		temp = list_maps->next;
		array[i++] = *((t_map *)list_maps->content);
		ft_lstdelone(list_maps, free);
		list_maps = temp;
	}
	return (array);
}

t_map *parse_gif(const char *path, int *image_count) {
	const int fd = open(path, O_RDONLY);
	t_gif_header info;
	t_color glob_coltable[256];
	t_map *maps;

	*image_count = 0;
	if (fd < 0)
		return (NULL);
	info = parse_header(fd);
	if (ft_strncmp(info.signature, "GIF", 3) || !(info.version[0] == '8')) {
		close(fd);
		return (NULL);
	}
	if (info.packed & 0b10000000)
		parse_color_table(glob_coltable, (int)1 << ((info.packed & 0b0111) + 1),
											fd);
	maps = parse_allimg(fd, image_count, glob_coltable);
	close(fd);
	return (maps);
}

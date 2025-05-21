#include <color.h>
#include <gif_parse.h>
#include <map.h>
#include <fcntl.h>
#include <stdint.h> //various int types
#include <string.h> //memset
#include <unistd.h> //read comes here
#include <stdlib.h> //mallocs and frees and such
#include <libft.h> //the list functions

//called after the image separator byte (2C)
//does not accept interlacing
t_map	*parse_image(const t_color *const table, int fd)
{
	t_gifmap	map;
	char		lzw;
	uint16_t		size[2];

	map.map = malloc(sizeof(t_map));
	map.cltab = table;
	//skip the image alignment and ignore it
	read(fd, size, 4);
	//TODO parse size and create a map to pass to parse block
	read(fd, size, 4);
	map.map->size.x = size[0];
	map.map->size.y = size[1];
	new_map(map.map);
	read(fd, &lzw, 1);
	while (parse_block(lzw, fd, &map))
		;
	return (map.map);
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
		table[i].color = 0;
		read(fd, table + i, 3);
		i++;
	}
}

t_map	*parse_allimg(const int fd, int *image_count,
		const t_color *const cltab)
{
	t_list	*list_maps;
	t_list	*temp;
	t_map	*array;
	char	buffer[8];
	int		i;

	read(fd, buffer + 7, 1);
	while (buffer[7] == 0x21)
		read(fd, buffer, 8);
	list_maps = NULL;
	while (buffer[7] == 0x2C)
	{
		ft_lstadd_back(&list_maps, ft_lstnew(parse_image(cltab, fd)));
		read(fd, buffer + 6, 2);
	}
	*image_count = ft_lstsize(list_maps);
	array = malloc(sizeof(t_map) * (*image_count));
	i = 0;
	while (list_maps)
	{
		temp = list_maps->next;
		array[i] = *((t_map *) list_maps->content);
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
	if (strncmp(info.signature, "GIF", 3) || !(info.packed & 0b10000000))
	{
		if (!(info.packed & 0b1000000))
			write(2, "GIF HAS LOCAL COLOR TABLES\n", 27);
		else
			write(2, "THIS IS NOT A GIF\n", 18);
		close(fd);
		return (NULL);
	}
	parse_color_table(glob_coltable, (int) 1 << ((info.packed & 0b0111) + 1), fd);
	maps = parse_allimg(fd, image_count, glob_coltable);
	close (fd);
	return (maps);
}

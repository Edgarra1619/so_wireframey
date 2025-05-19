#include <color.h>
#include <gif_parse.h>
#include <map.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
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

char	*parse_block(const t_color *const cltab, size_t ctsize, char lzw, const int fd)
{
	unsigned char	block_size;
	size_t			bits_read;
	char	data[256];
	t_giftree	*const codetab = start_tree(ctsize);
	int				code;
	int				prev_code;

	read(fd, &block_size, 1);
	read(fd, data, block_size);
	//block_size * 8 / lzw; WARN this is the max size for the data
	//the actual size will be computed over the execution of the parser
	//pseudo implementation TODO actually finish this
	bits_read = 0;
	code = bitshift_left(lzw, data, block_size);
	put_code(code, codetab, stream);
	while (bits_read + lzw < block_size * 8)
	{
		prev_code = code;
		code = bitshift_left(lzw, data, block_size);
		if (find_code(code, codetab))
		{
			put_code(code, codetab, stream);
			new_code(code, prev_code, codetab);
		}
		else
		{
			put_code(new_code(prev_code, prev_code, codetab), codetab, stream);
		}
		bits_read += lzw;
	}
}

void	parse_image(t_color *table, int size, int fd)
{





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

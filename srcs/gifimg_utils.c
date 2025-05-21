#include <map.h>
#include <vector.h>
#include <color.h>
#include <unistd.h>
#include <gif_parse.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>

static void	add_to_map(t_gifmap *const map, const t_color color)
{
	if (map->offset.y > map->map->size.y)
		return ;
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
static unsigned int	bitshift_left(const size_t shift, unsigned char *data, size_t size)
{
	const size_t		byte_shift = shift / 8;
	const unsigned char	mask = -1 << (8 - (shift % 8));
	size_t				i;
	unsigned int		result;

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
	i = 0;
	result = (result << (shift % 8)) | ((data[0] & mask) >> (8 - (shift % 8)));
	while (i < size - 1)
	{
		data[i] = (data[i] << (shift % 8)) |
			((data[i + 1] & mask) >> (8 - (shift % 8)));
		i++;
	}
	data[size - byte_shift - 1] = data[size - byte_shift - 1] << (shift % 8);
	return (result);
}

static int new_code(int first_index, t_ctable *const tab)
{
	int		code;
	t_code	*new_tab;

	code = first_index;
	while (tab->table[code].last_index != -1)
		code++;
	while (tab->table[first_index].prev_code != -1 &&
			tab->table[first_index].prev_code != first_index)
		first_index = tab->table[first_index].prev_code;
	//TODO put ft_memcpy and ft_memset
	if (code == ((int) 1 << tab->code_size) - 1)
	{
		new_tab = malloc(sizeof(t_code) * ((int) 1 << ++(tab->code_size)));
		//TODO guard this
		memset(new_tab, -1, sizeof(t_code) * ((int) 1 << tab->code_size));
		memcpy(new_tab, tab->table,
				sizeof(t_code) * ((int) 1 << (tab->code_size - 1)));
		free(tab->table);
		tab->table = new_tab;
	}
	tab->table[code].last_index = first_index;
	tab->table[code].prev_code = tab->prev_code;
	return (code);
}

static void	put_code(const int code, t_ctable *const tab,
		t_gifmap *const map)
{
	if (tab->table[code].prev_code != -1 && tab->table[code].prev_code != code)
		put_code(tab->table[code].prev_code, tab, map);
	add_to_map(map, map->cltab[tab->table[code].last_index]);
	tab->prev_code = code;
}

t_code	*new_table(const unsigned char lzw)
{
	t_code	*const new_tab = malloc(sizeof(t_code) * ((unsigned int) 1 << (lzw + 1)));
	unsigned int	i;

	if (!new_tab)
		return (NULL);
	//put ft_memset here
	i = 0;
	while (i < (1 << lzw) + 2)
	{
		new_tab[i].last_index = i;
		new_tab[i++].prev_code = -1;
	}
	while (i < (1 << (lzw + 1)))
	{
		new_tab[i].last_index = -1;
		new_tab[i++].prev_code = -1;
	}
	return (new_tab);
}

static void	clear_code(t_ctable *const tab)
{
	tab->prev_code = 0;
	tab->code_size = tab->lzw + 1;
	free(tab->table);
	tab->table = new_table(tab->lzw);
	//TODO MEGA guard this
}

static int	solve_code(int code, t_ctable *const tab,
	t_gifmap *const map)
{
	if (code == ((int) 1 << tab->lzw) + 1)
		tab->prev_code = code;
	else if (code == (int) 1 << tab->lzw)
		clear_code(tab);
	else if (tab->table[code].last_index == -1)
		put_code(new_code(tab->prev_code, tab), tab, map);
	else
	{
		new_code(code, tab);
		put_code(code, tab, map);
	}
	return (code);
}

//returns 0 on end of image
char	parse_block(const char lzw, const int fd, t_gifmap *const map)
{
	unsigned char	block_size;
	size_t			bits_read;
	unsigned char			data[256];
	t_ctable		codetab;

	read(fd, &block_size, 1);
	if (!block_size)
		return (1);
	read(fd, data, block_size);
	codetab.lzw = lzw;
	codetab.table = NULL;
	clear_code(&codetab);
	put_code(bitshift_left(codetab.code_size, data, block_size),
		&codetab, map);
	bits_read = codetab.code_size;
	while (bits_read + codetab.code_size < block_size * 8)
	{
		bits_read += codetab.code_size;
		if (solve_code(bitshift_left(codetab.code_size, data, block_size),
				&codetab, map) == (int) 1 << lzw)
		{
			bits_read += codetab.code_size;
			put_code(bitshift_left(codetab.code_size, data, block_size),
					&codetab, map);
		}
		else if (codetab.prev_code == ((int) 1 << lzw) + 1)
			break;
	}
	free(codetab.table);
	return (1);
}

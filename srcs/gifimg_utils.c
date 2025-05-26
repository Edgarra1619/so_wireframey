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
	map->map->color_map[map->offset % map->map->size.x][map->offset / map->map->size.x] = color;
	map->map->height_map[map->offset % map->map->size.x][map->offset / map->map->size.x] = 
		color.s_rgba.r + color.s_rgba.g + color.s_rgba.b;
	map->offset++;
}
/*
static unsigned int	bitshift_left(size_t shift,
			unsigned char *const data, size_t size)
{
	size_t				i;
	uint16_t			result;
	const unsigned char	mask = (unsigned char) -1 << (shift % 8);

	result = data[0] * (shift >= 8) << (shift % 8) | (data[shift >= 8] >> (8 - shift % 8));
	i = 0;
	while (i < size - 1 - shift / 8)
	{
		data[i] = (data[i + shift / 8] << (shift % 8)) |
			(data[i + 1 + shift / 8] & mask >> (8 - (shift % 8)));
		i++;
	}
	while (i < size)
		data[i++] = 0;
	return (result);
}
*/
static unsigned int	bitshift_left(size_t shift, unsigned char *const data, size_t size)
{
	uint16_t		result;
	size_t			i;

	result = ((1 << shift) - 1) & (data[0] | (int) data[1] << 8);
	i = 0;
	
	while(shift / 8 && i < size)
	{
		if(i == size - 1)
			data[i] = 0;
		else
			data[i] = data[i + 1];
		i++;
	}
	i = 0;
	while (i < size - 1)
	{
		data[i] = ((int)data[i] >> shift % 8) | ((int)data[i + 1] << (8 - shift % 8));
		i++;
	}
	data[i] >>=  shift;
	return(result);
}
static int new_code(int first_index, t_ctable *const tab)
{
	int		code;
	t_code	*new_tab;

	if(tab->code_size == 12)
		return (first_index);
	code = (int) 1 << tab->lzw;
	while (code < ((int) 1 << tab->code_size) && tab->table[code].last_index != -1)
		code++;
	while (tab->table[first_index].prev_code != -1 &&
			tab->table[first_index].prev_code != first_index)
		first_index = tab->table[first_index].prev_code;
	//TODO put ft_memcpy and ft_memset
	if (code == (((int) 1 << tab->code_size) - 1))
	{
		new_tab = malloc(sizeof(t_code) * ((size_t) 1 << ++(tab->code_size)));
		//TODO guard this
		ft_memset(new_tab, -1, sizeof(t_code) * ((size_t) 1 << tab->code_size));
		ft_memcpy(new_tab, tab->table,
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
	while (i < ((unsigned int) 1 << lzw) + 2)
	{
		new_tab[i].last_index = i;
		new_tab[i++].prev_code = -1;
	}
	while (i < ((unsigned int) 1 << (lzw + 1)))
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
	const int	cc = (int) 1 << (int) tab->lzw;

	if (code == cc)
		clear_code(tab);
	else if (code == ((int) 1 << tab->lzw) + 1)
		tab->prev_code = code;
	else if (tab->table[code].last_index == -1)
		put_code(new_code(tab->prev_code, tab), tab, map);
	else
	{
		new_code(code, tab);
		put_code(code, tab, map);
	}
	return (code);
}

unsigned char	*read_data(const int fd, size_t *const size)
{
	unsigned char	block_size;
	void			*data;
	void			*temp;
	size_t			current_size;

	*size = 0;
	data = NULL;
	current_size = 0;
	read(fd, &block_size, 1);
	while (block_size)
	{
		if ((*size + block_size) > current_size)
		{
			temp = malloc(current_size + 255 * 16 + 1);
			current_size += 255 * 16;
			memcpy(temp, data, *size);
			free(data);
			data = temp;
		}
		read(fd, data + *size, block_size);
		*size += block_size;
		read(fd, &block_size, 1);
	}
	((char *)data)[*size] = 0;
	return(data);
}

//this needs to have ALL of the blocks at the same time;
//returns 0 on end of image
char	parse_imgdata(const char lzw, const int fd, t_gifmap *const map)
{
	size_t			data_size;
	size_t			bits_read;
	t_ctable		codetab;
	unsigned char	*data;

	data = read_data(fd, &data_size);
	codetab.lzw = lzw;
	codetab.table = NULL;
	clear_code(&codetab);
	bits_read = 0;
	while (bits_read + codetab.code_size < (unsigned int) data_size * 8)
	{
		bits_read += codetab.code_size;
		if (solve_code(bitshift_left(codetab.code_size, data, data_size),
				&codetab, map) == (int) 1 << lzw)
		{
			bits_read += codetab.code_size;
			put_code(bitshift_left(codetab.code_size, data, data_size),
					&codetab, map);
		}
		else if (codetab.prev_code == ((int) 1 << lzw) + 1)
			break;
	}
	free(codetab.table);
	free(data);
	return (1);
}

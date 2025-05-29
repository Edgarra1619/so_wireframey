#include <map.h>
#include <vector.h>
#include <color.h>
#include <unistd.h>
#include <gif_parse.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>
#include <state.h>
#include <mlx.h>

//MAKE THIS CONSIDER TRANSPARENT
static void	add_to_map(t_gifmap *const map, const t_color color)
{
	if (color.s_rgba.a)
	{
		map->map->color_map[map->offset % map->map->size.x][map->offset / map->map->size.x] = color;
		map->map->height_map[map->offset % map->map->size.x][map->offset / map->map->size.x] = 
			color.s_rgba.r + color.s_rgba.g + color.s_rgba.b;
	}
	else
	{
		map->map->color_map[map->offset % map->map->size.x]
			[map->offset / map->map->size.x] = map->fmap->color_map
			[map->offset % map->map->size.x + map->map->position.x]
			[map->offset / map->map->size.x + map->map->position.y];
		map->map->height_map[map->offset % map->map->size.x]
			[map->offset / map->map->size.x] = map->fmap->height_map
			[map->offset % map->map->size.x + map->map->position.x]
			[map->offset / map->map->size.x + map->map->position.y];
	}
	map->offset++;
}

static unsigned int	extract_bits(size_t shift, t_gifdata *const data)
{
	unsigned int	result;
	size_t			i;

	result = 0;
	i = 0;
	while (i < shift)
	{
		result = result | ((1 & (data->data[data->bytes] >> data->bits)) << i++);
		data->bytes += (data->bits + 1) / 8;
		data->bits = (data->bits + 1) % 8;
	}
	return (result);
}

static int new_code(int first_index, t_ctable *const tab)
{
	int		code;
	t_code	*new_tab;

	code = (int) 1 << tab->lzw;
	while (code < ((int) 1 << tab->code_size) && tab->table[code].last_index != -1)
		code++;
	while (tab->table[first_index].prev_code != -1 &&
			tab->table[first_index].prev_code != first_index)
		first_index = tab->table[first_index].prev_code;
	//TODO put ft_memcpy and ft_memset
	if (code == (((int) 1 << tab->code_size) - 1))
	{
		if(tab->code_size == 12)
			return (first_index);
		new_tab = malloc(sizeof(t_code) * ((size_t) 1 << ++(tab->code_size)));
		//TODO guard this
		ft_memset(new_tab + (1 << (tab->code_size - 1)), -1, sizeof(t_code) * ((size_t) 1 << (tab->code_size - 1)));
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

unsigned char	*read_data(const int fd, t_gifdata *const data)
{
	unsigned char	block_size;
	void			*temp;
	size_t			current_size;

	ft_bzero(data, sizeof(*data));
	current_size = 0;
	read(fd, &block_size, 1);
	while (block_size)
	{
		if ((data->size + block_size) > current_size)
		{
			temp = malloc(current_size + 255 * 16 + 1);
			current_size += 255 * 16;
			ft_memcpy(temp, data->data, data->size);
			free(data->data);
			data->data = temp;
		}
		read(fd, data->data + data->size, block_size);
		data->size += block_size;
		read(fd, &block_size, 1);
	}
	data->data[data->size] = 0;
	return(data->data);
}

//this needs to have ALL of the blocks at the same time;
//returns 0 on end of image
char	parse_imgdata(const char lzw, const int fd, t_gifmap *const map)
{
	size_t		bits_read;
	t_ctable	codetab;
	t_gifdata	data;

	read_data(fd, &data);
	codetab.lzw = lzw;
	codetab.table = NULL;
	clear_code(&codetab);
	bits_read = 0;
	while (bits_read + codetab.code_size < (unsigned int) data.size * 8)
	{
		bits_read += codetab.code_size;
		if (solve_code(extract_bits(codetab.code_size, &data),
				&codetab, map) == (int) 1 << lzw)
		{
			bits_read += codetab.code_size;
			put_code(extract_bits(codetab.code_size, &data),
					&codetab, map);
		}
		else if (codetab.prev_code == ((int) 1 << lzw) + 1)
			break;
	}
	free(codetab.table);
	free(data.data);
	return (1);
}

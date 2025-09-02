/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gifimg_utils2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:36:41 by edgribei          #+#    #+#             */
/*   Updated: 2025/09/02 15:36:45 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gif_parse_bonus.h>
#include <stdlib.h>

void	add_to_map(t_gifmap *const map, const t_color color)
{
	const t_vec2	pos = (t_vec2)
	{map->map->position.x + (map->offset % map->map->size.x),
		map->map->position.y + map->offset / map->map->size.x};

	if (color.a)
	{
		map->map->color_map[pos.x][pos.y] = color;
		map->map->height_map[pos.x][pos.y] = color.r + color.g + color.b;
	}
	map->offset++;
}

unsigned int	extract_bits(size_t shift, t_gifdata *const data)
{
	unsigned int	result;
	size_t			i;

	result = 0;
	i = -1;
	while (++i < shift)
	{
		result = result | ((1 & (data->data[data->bytes] >> data->bits)) << i);
		data->bytes += (data->bits + 1) / 8;
		data->bits = (data->bits + 1) % 8;
	}
	return (result);
}

t_code	*increase_table(t_ctable *tab)
{
	t_code *const	new_tab
		= malloc(sizeof(t_code) * ((size_t) 1 << ++(tab->code_size)));

	if (new_tab)
	{
		ft_memset(new_tab + (1 << (tab->code_size - 1)), -1,
			sizeof(t_code) * ((size_t) 1 << (tab->code_size - 1)));
		ft_memcpy(new_tab, tab->table,
			sizeof(t_code) * ((int) 1 << (tab->code_size - 1)));
	}
	free(tab->table);
	tab->table = new_tab;
	if (!new_tab)
		tab->prev_code = 1 + (1 << tab->lzw);
	return (new_tab);
}

int	new_code(int first_index, t_ctable *const tab)
{
	int		code;

	code = (int) 1 << tab->lzw;
	while (code < ((int) 1 << tab->code_size)
		&& tab->table[code].last_index != -1)
		code++;
	while (tab->table[first_index].prev_code != -1
		&& tab->table[first_index].prev_code != first_index)
		first_index = tab->table[first_index].prev_code;
	if (code == (((int) 1 << tab->code_size) - 1))
	{
		if (tab->code_size == 12)
			return (first_index);
		if (!increase_table(tab))
			return (-1);
	}
	tab->table[code].last_index = first_index;
	tab->table[code].prev_code = tab->prev_code;
	return (code);
}

void	put_code(const int code, t_ctable *const tab, t_gifmap *const map)
{
	if (code < 0)
		return ;
	if (tab->table[code].prev_code != -1 && tab->table[code].prev_code != code)
		put_code(tab->table[code].prev_code, tab, map);
	add_to_map(map, map->cltab[tab->table[code].last_index]);
	tab->prev_code = code;
}

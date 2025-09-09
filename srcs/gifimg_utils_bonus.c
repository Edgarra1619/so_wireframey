/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gifimg_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:36:20 by edgribei          #+#    #+#             */
/*   Updated: 2025/09/02 15:36:27 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map.h>
#include <vector.h>
#include <color.h>
#include <unistd.h>
#include <gif_parse_bonus.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>
#include <state.h>
#include <mlx.h>

void			add_to_map(t_gifmap *const map, const t_color color);
unsigned int	extract_bits(size_t shift, t_gifdata *const data);
t_code			*increase_table(t_ctable *tab);
int				new_code(int first_index, t_ctable *const tab);
void			put_code(const int code,
					t_ctable *const tab, t_gifmap *const map);

t_code	*new_table(const unsigned char lzw)
{
	t_code *const	new_tab
		= malloc(sizeof(t_code) * ((unsigned int) 1 << (lzw + 1)));
	unsigned int	i;

	if (!new_tab)
		return (NULL);
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

	current_size = 0;
	read(fd, &block_size, 1);
	while (block_size)
	{
		if ((data->size + block_size) > current_size)
		{
			temp = malloc(current_size + 255 * 16 + 1);
			current_size += 255 * 16;
			if (temp)
				ft_memcpy(temp, data->data, data->size);
			free(data->data);
			data->data = temp;
			if (!temp)
				return (NULL);
		}
		read(fd, data->data + data->size, block_size);
		data->size += block_size;
		read(fd, &block_size, 1);
	}
	data->data[data->size] = 0;
	return (data->data);
}

//this needs to have ALL of the blocks at the same time;
char	parse_imgdata(const char lzw, const int fd, t_gifmap *const map)
{
	size_t		bits_read;
	t_ctable	codetab;
	t_gifdata	data;

	ft_bzero(&data, sizeof(data));
	read_data(fd, &data);
	codetab = (t_ctable){0, 0, lzw, 0};
	clear_code(&codetab);
	bits_read = 0;
	while (bits_read + codetab.code_size < (unsigned int) data.size * 8
		&& codetab.table && data.data)
	{
		bits_read += codetab.code_size;
		if (solve_code(extract_bits(codetab.code_size, &data),
				&codetab, map) == (int) 1 << lzw && codetab.table)
		{
			bits_read += codetab.code_size;
			put_code(extract_bits(codetab.code_size, &data), &codetab, map);
		}
		else if (codetab.prev_code == ((int) 1 << lzw) + 1)
			break ;
	}
	free(codetab.table);
	free(data.data);
	return (1);
}

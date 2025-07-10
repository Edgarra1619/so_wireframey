/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:55:56 by edgribei          #+#    #+#             */
/*   Updated: 2025/06/16 17:39:07 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <map.h>
#include <mlx.h>
#include <render.h>
#include <state.h>
#include <stdlib.h>
#include <parse.h>

void	free_state(t_state *const state)
{
	free_map((void **)state->pre_map);
	free_maps(state->maps, state->mapcount);
	if (state->mlx)
	{
		if (state->buffer.ptr)
			mlx_destroy_image(state->mlx, state->buffer.ptr);
		mlx_destroy_window(state->mlx, state->window);
		mlx_destroy_display(state->mlx);
		free(state->mlx);
	}
}

static void	error_out(t_state *const state, const char *const errmsg)
{
	free_state(state);
	ft_putendl_fd(errmsg, 2);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_state	state;

	ft_bzero(&state, sizeof(state));
	if (argc != 2)
		error_out(&state, "Wrong number of arguments");
	if (parse_file(argv[1], &state))
		error_out(&state, "Error while parsing file (is the path correct?)");
	state.camera.pos
		= (t_vecf3){-state.maps->size.x / 2.0, -state.maps->size.y / 2.0, 0};
	state.camera.vertical_scale = 5;
	state.camera.rot = (t_vecf2){0, 90};
	state.camera.zoom = 1;
	if (pre_map_alloc(&state) == -1)
		error_out(&state, "Error while preparing");
	if (safe_start_mlx(&state))
		error_out(&state, "Something happened while opening window!");
	free_state(&state);
}

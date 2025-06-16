/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edgribei <edgribei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:57:45 by edgribei          #+#    #+#             */
/*   Updated: 2025/06/16 19:58:00 by edgribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include <color.h>
# include <state.h>

typedef struct s_heicol
{
	int		height;
	t_color	color;
}	t_heicolor;
int	parse_file(const char *path, t_state *state);

#endif
